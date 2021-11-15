/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:35:12 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:46:01 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_cmds(char	**arg)
{
	char	**ret;
	char	*pos;
	int		idx;
	int		ret_idx;

	ret = (char **)malloc(sizeof(char *) * (64 + 1));
	idx = 0;
	ret_idx = 0;
	while (arg[++idx] != NULL && idx < 64)
	{
		pos = ft_strchr(arg[idx], '=');
		if (pos != NULL && arg[idx][0] != '=' \
		&& *(pos + 1) != ' ' && *(pos + 1) != '\0')
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
		cmds = make_cmds(exe->cmd_arg);
		idx = -1;
		while (cmds[++idx] != NULL)
			pp_export(cmds[idx], &g_data.exp_lst, &g_data.env_lst);
		free_args(cmds);
	}
	else if (ft_strcmp("unset", (*line_lst)->content) == 0 \
		&& (*line_lst)->next != NULL)
	{
		command_arg(line_lst, exe);
		idx = 0 ;
		while (exe->cmd_arg[++idx] != NULL)
			pp_unset(exe->cmd_arg[idx], &g_data.exp_lst, &g_data.env_lst);
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
