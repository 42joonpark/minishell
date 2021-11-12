#include "minishell.h"

static void	print_env_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
}

int	pp_env(t_lst **env_lst)
{
	print_env_lst(*env_lst);
	return (EXIT_SUCCESS);
}
