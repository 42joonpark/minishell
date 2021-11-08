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

static int	add_exp_lst(t_lst *env_lst1)
{
	t_lst	*new;

	if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
	{
		new = pp_lstnew(ft_strdup(env_lst1->content), -1);
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
