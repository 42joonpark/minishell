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
	if (chdir(dir) == -1)
	{
		syntax_error_msg2("cd", args[1], "No such file or directory");
		g_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}
