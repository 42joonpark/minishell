#include "minishell.h"

int	is_builtin(char *str)
{
	if (pp_strcmp(str, "echo") == 0 \
	|| pp_strcmp(str, "cd") == 0 \
	|| pp_strcmp(str, "pwd") == 0 \
	|| pp_strcmp(str, "export") == 0 \
	|| pp_strcmp(str, "unset") == 0 \
	|| pp_strcmp(str, "env") == 0)
		return (1);
	return (0);
}
