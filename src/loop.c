/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 18:20:13 by donpark          ###   ########.fr       */
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
		args = pp_split(line, ' ');
		//
		pp_pwd(args);
		free(line);
	}
}
