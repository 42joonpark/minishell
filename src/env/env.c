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
	if (env_lst == NULL)
	{
		g_data.exit_status = 126;
		return (EXIT_FAILURE);
	}
	print_env_lst(*env_lst);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}
