/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:22:00 by donpark           #+#    #+#             */
/*   Updated: 2021/10/30 18:17:58 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_max_idx(t_list **lst_ptr)
{
	t_list	*lst;
	int		max;

	lst = *lst_ptr;
	max = lst->id;
	while (lst != NULL)
	{
		if (max < lst->id)
			max = lst->id;
		lst = lst->next;
	}
	return (max);
}

static void	backtracking(int *flag, t_list **env_lst, t_list **env_lst1)
{
	if (*flag == 1)
	{
		*env_lst1 = *env_lst;
		*flag = 0;
	}
}

static int	add_exp_lst(t_list *env_lst1, t_list **exp_lst)
{
	t_list	*new;

	if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
	{
		new = pp_lstnew(pp_strdup(env_lst1->content));
		if (new == 0)
			return (EXIT_FAILURE);
		pp_lstadd_back(exp_lst, new);
	}
	return (EXIT_SUCCESS);
}

int	exp_list(t_list **exp_lst, t_list **env_lst)
{
	t_list	*env_lst1;
	int		i;
	int		flag;

	env_lst1 = *env_lst;
	i = 0;
	flag = 0;
	while (env_lst1 != NULL)
	{
		backtracking(&flag, env_lst, &env_lst1);
		if (env_lst1->id == i)
		{
			if (add_exp_lst(env_lst1, exp_lst))
				return (EXIT_FAILURE);
			if (i == get_max_idx(env_lst))
				break ;
			i++;
			flag = 1;
		}
		if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
			env_lst1 = env_lst1->next;
	}
	return (EXIT_SUCCESS);
}
