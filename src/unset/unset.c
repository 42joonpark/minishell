/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:26:16 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:26:17 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_return(void)
{
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}

int	pp_unset(char *args, t_lst **exp_lst, t_lst **env_lst)
{
	t_lst	*exp;
	t_lst	*env;
	t_lst	*tmp;

	if (args == NULL)
		return (unset_return());
	exp = *exp_lst;
	env = *env_lst;
	while (exp != NULL)
	{
		tmp = is_same_content_key(exp_lst, args);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		exp = exp->next;
	}
	while (env != NULL)
	{
		tmp = is_same_content_key(env_lst, args);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		env = env->next;
	}
	return (unset_return());
}
