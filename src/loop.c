/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 11:56:36 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop()
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
			pp_pwd(args);
		if (pp_strcmp(args[0], "echo") == 0)
			pp_echo(args);
		if (pp_strcmp(args[0], "cd") == 0)
			pp_cd(args);
		if (pp_strcmp(args[0], "exit") == 0)
			is_running = FALSE;
		free(line);
		//free(args);
	}
}
