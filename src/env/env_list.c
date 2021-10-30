/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:18:34 by donpark           #+#    #+#             */
/*   Updated: 2021/10/30 18:18:27 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list(t_list **env_lst, char **env)
{
	int		i;
	t_list	*new;

	i = 0;
	while (env[i] != NULL)
	{
		new = pp_lstnew(pp_strdup(env[i]));
		if (new == 0)
			return (EXIT_FAILURE);
		pp_lstadd_back(env_lst, new);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	put_env_index(t_list **env_lst)
{
	t_list	*env_lst1;
	t_list	*env_lst2;
	int		sorted_idx;

	env_lst1 = *env_lst;
	while (env_lst1 != NULL)
	{
		sorted_idx = 0;
		env_lst2 = *env_lst;
		while (env_lst2 != NULL)
		{
			if (pp_strcmp_limit(env_lst1->content, env_lst2->content, '=') > 0)
				sorted_idx++;
			env_lst2 = env_lst2->next;
		}
		env_lst1->id = sorted_idx;
		env_lst1 = env_lst1->next;
	}
}
