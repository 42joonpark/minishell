#include "minishell.h"

int	pp_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_data.exit_status = 126;
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}
