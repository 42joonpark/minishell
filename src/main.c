#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	argc = 0;
	argv = NULL;
	minishell_loop(env);
	return (0);
}
