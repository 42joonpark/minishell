/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:24:10 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/02 18:26:31 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_unset(char **args, t_lst **exp_lst, t_lst **env_lst)
{
	t_lst	*exp;
	t_lst	*env;
	t_lst	*tmp;

	if (args[1] == NULL)
		return (EXIT_SUCCESS);
	exp = *exp_lst;
	env = *env_lst;
	while (exp != NULL)
	{
		tmp = is_same_content_key(exp_lst, args[1]);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		exp = exp->next;
	}
	while (env != NULL)
	{
		tmp = is_same_content_key(env_lst, args[1]);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
