/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:30:51 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 13:55:14 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process_helper(t_lst *line_lst, t_exe *exe)
{
	command_arg(&line_lst, exe);
	if (is_builtin(exe->cmd_arg[0]))
		exe_builtin(exe);
	else
		exe_command(exe);
	exit(g_data.exit_status);
}

static void	find_cmd_builtin(t_lst **line_lst)
{
	while ((*line_lst) != NULL && (*line_lst)->next != NULL \
			&& (*line_lst)->id != PIP)
	{
		if ((*line_lst)->id == COMMAND || (*line_lst)->id == BUILTIN)
			break ;
		(*line_lst) = (*line_lst)->next;
	}
}

void	child_process(t_lst *line_lst, t_exe *exe, int i)
{
	redirect_connect(line_lst, exe);
	if (i == 0 && exe->pip_cnt == 0)
		find_cmd_builtin(&line_lst);
	else if (i % 2 == 0 && exe->pip_cnt == 0)
		connect_pipe(exe->b, STDIN_FILENO);
	else if (i % 2 != 0 && exe->pip_cnt == 0)
		connect_pipe(exe->a, STDIN_FILENO);
	else if (i % 2 == 0 && exe->pip_cnt > 0)
	{
		if (exe->flag_b != 0)
			connect_pipe(exe->b, STDIN_FILENO);
		connect_pipe(exe->a, STDOUT_FILENO);
	}
	else if (i % 2 != 0 && exe->pip_cnt > 0)
	{
		connect_pipe(exe->a, STDIN_FILENO);
		connect_pipe(exe->b, STDOUT_FILENO);
	}
	child_process_helper(line_lst, exe);
}
