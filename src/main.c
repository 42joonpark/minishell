#include "minishell.h"
/*
int	main(int argc, char *argv[], char **env)
{
	argc = 0;
	argv = NULL;
	minishell_loop(env);
	return (0);
}
*/

/*
int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}
*/

void	env_list(t_list **env_lst, char **env)
{
	int		i;
	t_list	*new;

	i = 0;
	while (env[i] != NULL)
	{
		new = pp_lstnew((void *)env[i]);
		pp_lstadd_back(env_lst, new);
		i++;
	}
}

void	print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		write(1, lst->content, pp_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
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
		env_lst1->init_sort_idx = sorted_idx;
		env_lst1 = env_lst1->next;
	}
}

void	exp_list(t_list **exp_lst, t_list **env_lst)
{
	t_list	*env_lst1;
	t_list	*new;
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	env_lst1 = *env_lst;
	while (env_lst1 != NULL)
	{
		if (flag == 1)
		{
			env_lst1 = *env_lst;
			flag = 0;
		}
		if (env_lst1->init_sort_idx == j)
		{
			if (pp_strcmp_limit(env_lst1->content, "_=", '=') != 0)
			{
				new = pp_lstnew(env_lst1->content);
				pp_lstadd_back(exp_lst, new);
			}
			j++;
			flag = 1;
		}
		env_lst1 = env_lst1->next;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_list	*env_lst;
	t_list	*exp_lst;


	env_lst = NULL;
	env_list(&env_lst, env);
	put_env_index(&env_lst);
	print_lst(env_lst);

	exp_lst = NULL;
	exp_list(&exp_lst, &env_lst);
	print_lst(exp_lst);
	return (0);
}
