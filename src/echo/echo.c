/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:21:40 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 19:50:08 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_echo(char **args)
{
	if (pp_strcmp(args[0], "echo"))
		return (0);
	if (pp_strcmp(args[1], "-n") == 0)
		write(1, args[2], pp_strlen(args[2]));
	else
	{
		write(1, args[1], pp_strlen(args[1]));
		write(1, "\n", 1);
	}
	return (1);
}
