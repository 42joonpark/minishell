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

void	connect_pipe(int fd[], int io)
{
	dup2(fd[io], io);
	close(fd[READ]);
	close(fd[WRITE]);
}

void	close_pipe(int fd[])
{
	close(fd[READ]);
	close(fd[WRITE]);
}

int	redirect_in(char *file, t_exe *exe)
{
	exe->redir_in = open(file, O_RDONLY);
	if (exe->redir_in < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_in, STDIN_FILENO);
	close(exe->redir_in);
	return (EXIT_SUCCESS);
}

int	redirect_out(char *file, t_exe *exe)
{
	exe->redir_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (exe->redir_out < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_out, STDOUT_FILENO);
	close(exe->redir_out);
	return (EXIT_SUCCESS);
}

int	redirect_append(char *file, t_exe *exe)
{
	exe->redir_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (exe->redir_out < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_out, STDOUT_FILENO);
	close(exe->redir_out);
	return (EXIT_SUCCESS);
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

int	pipe_count(t_lst *line_lst)
{
	int	cnt;

	cnt = 0;
	while (line_lst != NULL)
	{
		if (line_lst->id == PIP)
			cnt++;
		line_lst = line_lst->next;
	}
	return (cnt);
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
/*
void	exe_builtin(char **cmd_arg)
{
	if (ft_strcmp(cmd_arg[0], "cd") == 0)
		pp_cd(&cmd_arg[1]);
	else if (ft_strcmp(cmd_arg[0], "echo") == 0)
		pp_echo(&cmd_arg[1]);
	else if (ft_strcmp(cmd_arg[0], "env") == 0)
		pp_env(&g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "export") == 0)
		pp_export(cmd_arg, &g_data.exp_lst, &g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "pwd") == 0)
		pp_pwd();
	else if (ft_strcmp(cmd_arg[0], "unset") == 0)
		pp_unset(cmd_arg, &g_data.exp_lst, &g_data.env_lst);
}
*/
void	exe_command(t_exe *exe)
{
	char	buf[P_BUFFER_SIZE];

	find_executable(exe->cmd_arg[0], convert_env(), buf, P_BUFFER_SIZE);
	execve(buf, exe->cmd_arg, convert_env());
}

/**
 * pipe 나오기 전까지 명령어는 하나이다.
 * redirect는 미리 열어 둘 수 있을 거 같다.
 * < file cmd
 * < file cmd | cmd
 * < file cmd | cmd > file
 */
int	execute(t_lst *line_lst)
{
	t_exe	*exe;
	pid_t	pid;
	int		status;
	int		i;
	int		flag_b;

	exe = (t_exe *)malloc(sizeof(t_exe));
	if (exe == NULL)
		exit(EXIT_FAILURE);
	exe->pip_cnt = pipe_count(line_lst);
	exe->redir_in = -1;
	exe->redir_out = -1;
	flag_b = 0;

	// command_arg(line_lst, exe);		// [test code] 나중에 삭제할 것.
	// exe_command(exe);				// [test code] 나중에 삭제할 것.
	i = 0;
	while (line_lst != NULL)
	{
		if (exe->pip_cnt > 0) // 1. pip_cnt = 1
		{
			if (i % 2 == 0)
				pipe(exe->a);	// 2. i == 0 이니까 처음에는 exe->a
			else
			{
				flag_b = 1;
				pipe(exe->b);
			}
		}
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			redirect_connect(line_lst, exe);	// 3.redirect_in : dup2(file_fd, STDIN_FILENO);

			if (i == 0 && exe->pip_cnt == 0)
			{
			}
			else if (i % 2 == 0 && exe->pip_cnt == 0)	//  파이프 마지막 명령 실행
			{
				connect_pipe(exe->b, STDIN_FILENO);
				// dup2(exe->b[READ], STDIN_FILENO);
			}
			else if (i % 2 != 0 && exe->pip_cnt == 0)	//  파이프 마지막 명령 실행
			{
				connect_pipe(exe->a, STDIN_FILENO);
				// dup2(exe->a[READ], STDIN_FILENO);	// 10. 실행
			}
			else if (i % 2 == 0 && exe->pip_cnt > 0)
			{
				if (flag_b != 0)
					connect_pipe(exe->b, STDIN_FILENO);
					// dup2(exe->b[READ], STDIN_FILENO);		// 일단 실행 안됬을것임. 		// 1
				connect_pipe(exe->a, STDOUT_FILENO);
				// dup2(exe->a[WRITE], STDOUT_FILENO);		// pipe(w) 연결
			}
			else if (i % 2 != 0 && exe->pip_cnt > 0)
			{
				connect_pipe(exe->a, STDIN_FILENO);
				// dup2(exe->a[READ], STDIN_FILENO);
				connect_pipe(exe->b, STDOUT_FILENO);
				// dup2(exe->b[WRITE], STDOUT_FILENO);
			}

			command_arg(&line_lst, exe);	// execve 사용할 **변수 생성.

			// if (is_builtin(exe->cmd_arg[0]))
			// 	exe_builtin(exe->cmd_arg);
			// else
				exe_command(exe);	// 8. cmd 실행하면 stdin에 들어있는 값을 pipe(w)로 보냄
			// exit(EXIT_SUCCESS);
		}
		else
		{
			if (i == 0 && exe->pip_cnt == 0)
			{
			}
			else if (i % 2 == 0 && exe->pip_cnt == 0)
			{
				close(exe->b[READ]);
				// close(exe->a[WRITE]);
				// close_pipe(exe->a);
			}
			else if (i % 2 != 0 && exe->pip_cnt == 0)
			{
				close(exe->a[READ]);
				// close(exe->b[WRITE]);
				// close_pipe(exe->b);
			}
			else if (i % 2 == 0 && exe->pip_cnt > 0)
			{
				close(exe->a[WRITE]);
				if (flag_b != 0)
					close(exe->b[READ]);	// 일단 실행 안될것임 		 // 2.
			}
			else if (i % 2 != 0 && exe->pip_cnt > 0)
			{
				close(exe->a[READ]);
				close(exe->b[WRITE]);
			}
			waitpid(pid, &status, 0);
		}
		i++;
		exe->pip_cnt--;
		while (line_lst != NULL && line_lst->id != PIP)
			line_lst = line_lst->next;
		if (line_lst == NULL)
		{
			free(exe);
			exe = NULL;
			break ;
		}
		else if (line_lst->id == PIP)
			line_lst = line_lst->next;
	}
	// fprintf(stderr, "=====================\n");
	return (EXIT_SUCCESS);
}
/*
int execute(t_lst *line_lst)
{
    t_exe   *exe;
    pid_t   pid;
    int     status;
    int     i;
    exe = (t_exe *)malloc(sizeof(t_exe));
    if (exe == NULL)
        exit(EXIT_FAILURE);
    exe->pip_cnt = pipe_count(line_lst);
    exe->redir_in = -1;
    exe->redir_out = -1;
    i = 0;
    int idx = 0;
    while (idx < 2)
    {
        if (idx == 0)
            pipe(exe->a);
        else
            pipe(exe->b);
        pid = fork();
        if (pid < 0)
            exit(EXIT_FAILURE);
        else if (pid == 0)
        {
            redirect_connect(line_lst, exe);
            if (idx == 0)
            {
                dup2(exe->a[WRITE], STDOUT_FILENO);
                close(exe->a[WRITE]);
                close(exe->a[READ]);
            }
            else
            {
                dup2(exe->a[READ], STDIN_FILENO);
                close(exe->a[READ]);
                close(exe->a[WRITE]);
            }
            command_arg(&line_lst, exe);    // {"wc",NULL}
            exe_command(exe);
        }
        else
        {
            if (idx == 0)
                close(exe->a[WRITE]);
            else
                close(exe->a[READ]);
            waitpid(pid, &status, 0);
            i++;
            exe->pip_cnt--;
            while (line_lst != NULL && line_lst->id != PIP)
                line_lst = line_lst->next;
            if (line_lst == NULL)
                break ;
            else if (line_lst->id == PIP)
                line_lst = line_lst->next;
        }
        ++idx;
    }
    // fprintf(stderr, "=====================\n");
    return (EXIT_SUCCESS);
}
*/
