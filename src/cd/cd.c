/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:28 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 18:26:40 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_cd(char **args)
{
	char	*default_dir;
	char	*dir;

	default_dir = getenv("HOME");
	if (args[1] == NULL)
		dir = default_dir;
	else
		dir = args[1];
	if (chdir(dir) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
