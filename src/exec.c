/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 21:05:19 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 13:53:11 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	exe_builtin(t_exe *exe)
{
	char	**cmd_arg;

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
		pp_export(NULL, &g_data.exp_lst, &g_data.env_lst);
	else if (ft_strcmp(cmd_arg[0], "unset") == 0)
		pp_unset(NULL, &g_data.exp_lst, &g_data.env_lst);
}

void	exe_command(t_exe *exe)
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
