/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:23:49 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/20 18:18:39 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_pwd(char **args)
{
	char	*pwd;

	if (pp_strcmp(args[0], "pwd"))
		return (0);
	pwd = getcwd(NULL, 0);
	write(1, pwd, pp_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (1);
}
