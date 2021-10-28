/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/25 15:09:05 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_list **env_lst, t_list **exp_lst)
{
	char	*line;
	char	**args;
	int		is_running;

	is_running = TRUE;
	while (is_running)
	{
		line = readline("> ");
		if (pp_strcmp(line, "\0") == 0)
			continue ;
		args = pp_split(line, ' ');
		if (pp_strcmp(args[0], "pwd") == 0)
			pp_pwd();
		if (pp_strcmp(args[0], "echo") == 0)
			pp_echo(args);
		if (pp_strcmp(args[0], "cd") == 0)
			pp_cd(args);
		if (pp_strcmp(args[0], "exit") == 0)
			is_running = FALSE;
		if (pp_strcmp(args[0], "env") == 0)
			pp_env(env_lst);
		if (pp_strcmp(args[0], "export") == 0)
			pp_export(args, exp_lst, env_lst);
		if (pp_strcmp(args[0], "unset") == 0)
			pp_unset(args, exp_lst, env_lst);
		free(line);
		//free(args);
	}

}
