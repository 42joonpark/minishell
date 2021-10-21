/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:46 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 11:54:03 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], pp_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
