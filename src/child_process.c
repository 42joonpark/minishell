#include "minishell.h"

static char	**convert_env(void)
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

static void	exe_builtin(t_exe *exe)
{
	char **cmd_arg;

	cmd_arg = exe->cmd_arg;
	if (ft_strcmp(cmd_arg[0], "cd") == 0 && exe->pip_cnt > 0)
		pp_cd(cmd_arg);
	else if (ft_strcmp(cmd_arg[0], "pwd") == 0)
		pp_pwd();
	else if (ft_strcmp(cmd_arg[0], "echo") == 0)
		pp_echo(&cmd_arg[1]);
	else if (ft_strcmp(cmd_arg[0], "env") == 0)
		pp_env(&g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "export") == 0 && cmd_arg[1] == NULL)
		//pp_export(cmd_arg[0], &g_data.exp_lst, &g_data.env_lst);
		pp_export(NULL, &g_data.exp_lst, &g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "unset") == 0)
		pp_unset(cmd_arg, &g_data.exp_lst, &g_data.env_lst);
}

static void	exe_command(t_exe *exe)
{
	char	buf[P_BUFFER_SIZE];

	ft_memset(buf, 0, P_BUFFER_SIZE);
	find_executable(exe->cmd_arg[0], convert_env(), buf, P_BUFFER_SIZE);
	if (buf[0] == '\0')
	{
		syntax_error_msg(exe->cmd_arg[0], "command not found");
		g_data.exit_status = 127;
	}
	else
	{
		g_data.exit_status = 0;
		execve(buf, exe->cmd_arg, convert_env());
	}
}

static void	child_process_helper(t_lst *line_lst, t_exe *exe)
{
	command_arg(&line_lst, exe);
	if (is_builtin(exe->cmd_arg[0]))
		exe_builtin(exe);
	else
		exe_command(exe);
	exit(g_data.exit_status);
}

void	child_process(t_lst *line_lst, t_exe *exe, int i)
{
	redirect_connect(line_lst, exe);
	if (i == 0 && exe->pip_cnt == 0)
	{
		while (line_lst != NULL && line_lst->id != PIP && line_lst->next != NULL)
		{
			if (line_lst->id == COMMAND || line_lst->id == BUILTIN)
				break ;
			line_lst = line_lst->next;
		}
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
	child_process_helper(line_lst, exe);
}