/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:24:10 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/25 15:01:48 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_unset(char **args, t_list **exp_lst, t_list **env_lst)
{
	t_list	*exp;
	t_list	*env;
	t_list	*tmp;

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
