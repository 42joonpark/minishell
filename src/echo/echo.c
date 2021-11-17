/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:23:40 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 15:40:01 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_echo(char **args, t_lst *line_lst)
{
	int	option;
	int	i;

	option = FALSE;
	line_lst = line_lst->next;
	i = 0;
	if (args[i] != NULL && (ft_strcmp(args[i], "-n") == 0))
	{
		option = TRUE;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL && line_lst != NULL && line_lst->space == TRUE)
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}
