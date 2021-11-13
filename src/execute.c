#include "minishell.h"

char	**convert_env(void)
{
	char	**env;
	int		total_l;
	int		i;
	t_lst	*env_lst;

	env_lst = g_data.env_lst;
	total_l = pp_lstsize(g_data.env_lst);
	env = (char **)malloc(sizeof(char *) * (total_l + 1));
	i = 0;
	while (i < total_l && env_lst != NULL)
	{
		env[i++] = ft_strdup(env_lst->content);
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

void	heredoc(t_lst *line_lst)
{
	int		fd[2];
	char	*buf;
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[READ]);
		ft_putstr_fd("> ", 1);
		while (get_next_line(STDIN_FILENO, &buf) != 0)
		{
			if (ft_strcmp(buf, line_lst->content) == 0)
				break ;
			ft_putstr_fd("> ", 1);
			ft_putendl_fd(buf, fd[WRITE]);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		connect_pipe(fd, STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
}

void	redirect_connect(t_lst *line_lst, t_exe *exe)
{
	while (line_lst != NULL && line_lst->id != PIP)
	{
		if (line_lst->id == REDIRIN)
			redirect_in(line_lst->next->content, exe);
		else if (line_lst->id == REDIROUT)
			redirect_out(line_lst->next->content, exe);
		else if (line_lst->id == APPEND)
			redirect_append(line_lst->next->content, exe);
		else if (line_lst->id == HEREDOC)
			heredoc(line_lst->next);
		line_lst = line_lst->next;
	}
}

int	check_arg(t_lst *line_lst)
{
	int	cnt;

	cnt = 0;
	while (line_lst != NULL && line_lst->id != PIP)
	{
		if (line_lst->id == ARG || line_lst->id == D_QUOTE || line_lst->id == S_QUOTE)
			cnt++;
		line_lst = line_lst->next;
	}
	return (cnt);
}

void	command_arg(t_lst **line_lst, t_exe *exe)
{
	int	arg_cnt;
	int	i;

	while ((*line_lst) != NULL && (*line_lst)->id != PIP)
	{
		if ((*line_lst)->id == COMMAND || (*line_lst)->id == BUILTIN)
		{
			arg_cnt = check_arg((*line_lst));
			exe->cmd_arg = (char **)malloc(sizeof(char *) * (arg_cnt + 2));
			exe->cmd_arg[0] = ft_strdup((*line_lst)->content);
			exe->cmd_arg[arg_cnt + 1] = NULL;
			(*line_lst) = (*line_lst)->next;
			i = 1;
			while ((*line_lst) != NULL && (*line_lst)->id != PIP)
			{
				if ((*line_lst)->id == ARG || (*line_lst)->id == D_QUOTE || (*line_lst)->id == S_QUOTE)
				{
					exe->cmd_arg[i++] = ft_strdup((*line_lst)->content);
				}
				(*line_lst) = (*line_lst)->next;
			}
			break ;
		}
		if ((*line_lst) != NULL)
			(*line_lst) = (*line_lst)->next;
	}
}

void	exe_builtin(char **cmd_arg)
{
	if (ft_strcmp(cmd_arg[0], "cd") == 0)
		pp_cd(cmd_arg);
	else if (ft_strcmp(cmd_arg[0], "pwd") == 0)
		pp_pwd();
	else if (ft_strcmp(cmd_arg[0], "echo") == 0)
		pp_echo(&cmd_arg[1]);
	else if (ft_strcmp(cmd_arg[0], "env") == 0)
		pp_env(&g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "export") == 0 && cmd_arg[1] == NULL)
		pp_export(cmd_arg, &g_data.exp_lst, &g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "unset") == 0)
		pp_unset(cmd_arg, &g_data.exp_lst, &g_data.env_lst);
}

void	exe_command(t_exe *exe)
{
	char	buf[P_BUFFER_SIZE];

	find_executable(exe->cmd_arg[0], convert_env(), buf, P_BUFFER_SIZE);
	execve(buf, exe->cmd_arg, convert_env());
}

void	child_process(t_lst *line_lst, t_exe *exe, int i)
{
	redirect_connect(line_lst, exe);

	if (i == 0 && exe->pip_cnt == 0)
	{
	}
	else if (i % 2 == 0 && exe->pip_cnt == 0)	//  파이프 마지막 명령 실행
		connect_pipe(exe->b, STDIN_FILENO);
	else if (i % 2 != 0 && exe->pip_cnt == 0)	//  파이프 마지막 명령 실행
		connect_pipe(exe->a, STDIN_FILENO);
	else if (i % 2 == 0 && exe->pip_cnt > 0)
	{
		if (exe->flag_b != 0)
			connect_pipe(exe->b, STDIN_FILENO);
		connect_pipe(exe->a, STDOUT_FILENO);		// cat(o)		wc(x)
	}
	else if (i % 2 != 0 && exe->pip_cnt > 0)
	{
		connect_pipe(exe->a, STDIN_FILENO);
		connect_pipe(exe->b, STDOUT_FILENO);		// grep(o)		wc(..)
	}

	command_arg(&line_lst, exe);

	if (is_builtin(exe->cmd_arg[0]))
		exe_builtin(exe->cmd_arg);
	else
		exe_command(exe);
	exit(EXIT_SUCCESS);
}

void	parent_process(t_exe *exe, pid_t pid, int i)
{
	int	status;

	if (i == 0 && exe->pip_cnt == 0)
	{
	}
	else if (i % 2 == 0 && exe->pip_cnt == 0)
		close(exe->b[READ]);
	else if (i % 2 != 0 && exe->pip_cnt == 0)
		close(exe->a[READ]);
	else if (i % 2 == 0 && exe->pip_cnt > 0)
	{
		close(exe->a[WRITE]);
		if (exe->flag_b != 0)
			close(exe->b[READ]);
	}
	else if (i % 2 != 0 && exe->pip_cnt > 0)
	{
		close(exe->a[READ]);
		close(exe->b[WRITE]);
	}
	waitpid(pid, &status, 0);
}

void	exe_free(t_exe *exe)
{
	int	idx;
	
	idx = 0;
	if (exe->cmd_arg != NULL)
	{
		while (exe->cmd_arg[idx] != NULL)
			free(exe->cmd_arg[idx++]);
		free(exe->cmd_arg);
	}
	free(exe);
	exe = NULL;
}

/*
 * TODO
 * builtin 실행 뒤 exit 안됨
 **************************************
 * pipe 나오기 전까지 명령어는 하나이다.
 * redirect는 미리 열어 둘 수 있을 거 같다.
 */
int	execute(t_lst *line_lst)
{
	t_exe	*exe;
	pid_t	pid;
	int		i;

	exe = (t_exe *)malloc(sizeof(t_exe));
	if (exe == NULL)
		exit(EXIT_FAILURE);
	exe->pip_cnt = pipe_count(line_lst);
	exe->redir_in = -1;
	exe->redir_out = -1;
	exe->flag_b = 0;
	exe->cmd_arg = NULL;
	i = 0;
	while (line_lst != NULL)
	{
		if (exe->pip_cnt > 0)
		{
			if (i % 2 == 0)
				pipe(exe->a);
			else
			{
				exe->flag_b = 1;
				pipe(exe->b);
			}
		}
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			child_process(line_lst, exe, i);
		}
		else
		{
			fprintf(stderr, "CHILD ID: %d\n", pid);
			parent_process(exe, pid, i);
		}
		if (is_builtin(line_lst->content) && exe->pip_cnt == 0)
		{
			if (ft_strcmp("cd", line_lst->content) == 0)
			{
				command_arg(&line_lst, exe);
				pp_cd(exe->cmd_arg);	// cd, cd dir
			}
			else if (ft_strcmp("export", line_lst->content) == 0)
			{

			}
			else if (ft_strcmp("unset", line_lst->content) == 0)
			{

			}
		}
		i++;
		exe->pip_cnt--;
		while (line_lst != NULL && line_lst->id != PIP)
			 line_lst = line_lst->next;
			/*
		while (line_lst != NULL)
		{
			if (line_lst->id == PIP)
				break ;
			line_lst = line_lst->next;
		}
		*/
		if (line_lst == NULL)
		{
			exe_free(exe);
			//free(exe);
			break ;
		}
		else if (line_lst->id == PIP)
			line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}