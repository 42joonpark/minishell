/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:28 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 10:28:18 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_cd(char **args)
{
	char	*default_dir;

	default_dir = NULL;
	if (args[0] == NULL)
		default_dir = getenv("HOME");
	else
		default_dir = args[0];
	chdir(default_dir);
	return (1);
}
