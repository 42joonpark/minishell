#include "minishell.h"

void	syntax_error(char *err)
{
	if (err != NULL)
	{
		write(2, err, pp_strlen(err));
		write(2, "\n", 1);
	}
}

void	print_error_msg(char *str, char *err);
{
	write(2, "ppsh: ", )
	if (str != NULL)
	{
		write(2, str, )
	}
}
