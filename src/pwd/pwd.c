/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:25:48 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:25:49 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_data.exit_status = 126;
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}
