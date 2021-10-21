/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:28 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 11:08:07 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_cd(char **args)
{
	char	*default_dir;

	default_dir = NULL;
	if (args[1] == NULL)
		default_dir = getenv("HOME");
	else
		default_dir = args[1];
	chdir(default_dir);
	return (1);
}
