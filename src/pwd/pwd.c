#include "minishell.h"

int	pp_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
