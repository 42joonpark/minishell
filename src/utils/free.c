/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:53:48 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 17:55:22 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_args(char **args)
{
	size_t	idx;

	idx = 0;
	while (args[idx] != NULL)
	{
		free(args[idx]);
		++idx;
	}
	free(args);
	return (EXIT_SUCCESS);
}
