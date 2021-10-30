#include "minishell.h"

void	syntax_error(char *err)
{
	if (err != NULL)
	{
		write(2, err, pp_strlen(err));
		write(2, "\n", 1);
	}
}
