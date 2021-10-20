/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/18 18:00:57 by joonpark         ###   ########.fr       */
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
		free(line);
	}
}
