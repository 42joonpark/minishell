#include "minishell.h"

int	pp_cd(char **args)
{
	char	*default_dir;
	char	*dir;

	default_dir = getenv("HOME");
	if (args[1] == NULL)
		dir = default_dir;
	else
		dir = args[1];
	if (chdir(dir) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
