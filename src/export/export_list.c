/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:24:53 by donpark           #+#    #+#             */
/*   Updated: 2021/11/18 14:47:38 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_max_idx(void)
{
	t_lst	*lst;
	int		max;

	lst = g_data.env_lst;
	max = lst->id;
	while (lst != NULL)
	{
		if (max < lst->id)
			max = lst->id;
		lst = lst->next;
	}
	return (max);
}

static void	backtracking(int *flag, t_lst **env_lst1)
{
	if (*flag == 1)
	{
		*env_lst1 = g_data.env_lst;
		*flag = 0;
	}
}

static void	create_content(t_lst *env_lst1, char **content)
{
	char	*key;
	char	*val;
	char	*tmp1;
	char	*tmp2;

	key = get_key(env_lst1->content);
	val = get_value(env_lst1->content);
	tmp1 = ft_strjoin(key, "=\"");
	tmp2 = ft_strjoin(tmp1, val);
	(*content) = ft_strjoin(tmp2, "\"");
	if (key != NULL)
		free(key);
	if (val != NULL)
		free(val);
	if (tmp1 != NULL)
		free(tmp1);
	if (tmp2 != NULL)
		free(tmp2);
}

static int	add_exp_lst(t_lst *env_lst1)
{
	t_lst	*new;
	char	*content;

	if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
	{
		create_content(env_lst1, &content);
		new = pp_lstnew(content, -1);
		if (new == 0)
			return (EXIT_FAILURE);
		pp_lstadd_back(&g_data.exp_lst, new);
	}
	return (EXIT_SUCCESS);
}

int	exp_list(void)
{
	t_lst	*env_lst1;
	int		i;
	int		flag;

	env_lst1 = g_data.env_lst;
	i = 0;
	flag = 0;
	while (env_lst1 != NULL)
	{
		backtracking(&flag, &env_lst1);
		if (env_lst1->id == i)
		{
			if (add_exp_lst(env_lst1))
				return (EXIT_FAILURE);
			if (i == get_max_idx())
				break ;
			i++;
			flag = 1;
		}
		if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
			env_lst1 = env_lst1->next;
	}
	return (EXIT_SUCCESS);
}
