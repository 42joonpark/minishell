/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:35:12 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:46:05 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	*init_exe(t_lst *line_lst)
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
