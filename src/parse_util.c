#include "minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 \
	|| ft_strcmp(str, "cd") == 0 \
	|| ft_strcmp(str, "pwd") == 0 \
	|| ft_strcmp(str, "export") == 0 \
	|| ft_strcmp(str, "unset") == 0 \
	|| ft_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	check_id(int id)
{
	if (id == HEREDOC || id == REDIRIN || id == REDIROUT \
	|| id == APPEND || id == PIP)
		return (1);
	else
		return (0);
}
