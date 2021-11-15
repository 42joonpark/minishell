#include "minishell.h"

static t_exe	*init_exe(t_lst *line_lst)
{
	t_exe	*exe;

	exe = (t_exe *)malloc(sizeof(t_exe));
	if (exe == NULL)
		exit(EXIT_FAILURE);
	exe->pip_cnt = pipe_count(line_lst);
	exe->redir_in = -1;
	exe->redir_out = -1;
	exe->flag_b = 0;
	exe->cmd_arg = NULL;
	return (exe);
}

static char	**function(char	**arg)
{
	char	**ret;
	char	*pos;
	int		idx;
	int		ret_idx;

	ret = (char **)malloc(sizeof(char *) * (64 + 1));
	idx = 0;
	ret_idx = 0;
	while (arg[++idx] != NULL)
	{
		pos = ft_strchr(arg[idx], '=');
		/*
		if (pos == NULL) // export b
			ret[ret_idx++] = ft_strdup(arg[idx]);
			*/
		if (pos != NULL && arg[idx][0] != '=' && *(pos + 1) != ' ' && *(pos + 1) != '\0') // export a=b
			ret[ret_idx++] = ft_strdup(arg[idx]);
		else
			syntax_error_msg2("export", arg[idx], "not a valid identifier");
	}
	ret[ret_idx] = NULL;
	return (ret);
}

static void	run_builtins_helper(t_lst **line_lst, t_exe *exe)
{
	int		idx;
	char	**cmds;

	if (ft_strcmp("export", (*line_lst)->content) == 0 \
		&& (*line_lst)->next != NULL)
	{
		command_arg(line_lst, exe);
		/*
		idx = 1;
		while (exe->cmd_arg[++idx] != NULL)
			ft_strcat(&exe->cmd_arg[1], exe->cmd_arg[idx]);
		if (exe->cmd_arg[1] != NULL)
			pp_export(exe->cmd_arg, &g_data.exp_lst, &g_data.env_lst);
			*/
		cmds = function(exe->cmd_arg);
		idx = -1;
		while (cmds[++idx] != NULL)
			pp_export(cmds[idx], &g_data.exp_lst, &g_data.env_lst);
// free cmds
	}
	
	else if (ft_strcmp("unset", (*line_lst)->content) == 0 \
		&& (*line_lst)->next != NULL)
	{
		command_arg(line_lst, exe);
		if (exe->cmd_arg[1] != NULL)
			pp_unset(exe->cmd_arg, &g_data.exp_lst, &g_data.env_lst);
	}
}

static void	run_builtins(t_lst **line_lst, t_exe *exe, int i)
{
	if (is_builtin((*line_lst)->content) && exe->pip_cnt == 0 && i == 0)
	{
		if (ft_strcmp("cd", (*line_lst)->content) == 0)
		{
			command_arg(line_lst, exe);
			pp_cd(exe->cmd_arg);
		}
		else
			run_builtins_helper(line_lst, exe);
	}
}

static void	run_command(t_lst **line_lst, t_exe *exe, int i)
{
	pid_t	pid;

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
		child_process(*line_lst, exe, i);
	else
		parent_process(exe, pid, i);
	run_builtins(line_lst, exe, i);
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
	int		i;

	exe = init_exe(line_lst);
	i = 0;
	while (line_lst != NULL)
	{
		run_command(&line_lst, exe, i);
		i++;
		exe->pip_cnt--;
		while (line_lst != NULL)
		{
			if (line_lst->id == PIP)
				break ;
			line_lst = line_lst->next;
		}
		if (line_lst == NULL)
		{
			exe_free(exe);
			break ;
		}
		else if (line_lst->id == PIP)
			line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}