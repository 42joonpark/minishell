/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 19:49:18 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(char **env)
{
	char	*line;
	char	**args;
	int		is_running;
	int		env_cnt;
	t_env	*env_list;

	env_list_alloc(env, &env_cnt, &env_list);
	save_env_data(env, env_cnt, env_list);
	is_running = TRUE;
	while (is_running)
	{
		line = readline("> ");
		if (pp_strcmp(line, "\0") == 0)
			continue ;
		args = pp_split(line, ' ');
		if (pp_strcmp(args[0], "pwd") == 0)
			pp_pwd(args);
		if (pp_strcmp(args[0], "echo") == 0)
			pp_echo(args);
		if (pp_strcmp(args[0], "cd") == 0)
			pp_cd(args);
		if (pp_strcmp(args[0], "exit") == 0)
			is_running = FALSE;
		if (pp_strcmp(args[0], "env") == 0)
			pp_env(env);
		if (pp_strcmp(args[0], "export") == 0)
			pp_export(args, env_cnt, env_list);
		free(line);
		//free(args);
	}
	free(env_list);
}
