#include "minishell.h"

int	env_list(char **env)
{
	int		i;
	t_lst	*new;

	i = 0;
	while (env[i] != NULL)
	{
		new = pp_lstnew(ft_strdup(env[i]), -1);
		if (new == 0)
			return (EXIT_FAILURE);
		pp_lstadd_back(&g_data.env_lst, new);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	put_env_index(void)
{
	t_lst	*env_lst1;
	t_lst	*env_lst2;
	int		sorted_idx;

	env_lst1 = g_data.env_lst;
	while (env_lst1 != NULL)
	{
		sorted_idx = 0;
		env_lst2 = g_data.env_lst;
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
