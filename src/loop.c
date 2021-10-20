/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 20:08:26 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop()
{
	char	*line;
	char	**args;

	while (TRUE)
	{
		line = readline("> ");
		if (pp_strcmp(line, "\0") == 0)
			continue ;
		args = pp_split(line, ' ');
			//
		pp_pwd(args);
		pp_echo(args);
		free(line);
	}
}
