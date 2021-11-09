#include "minishell.h"

void	syntax_error(char *err)
{
	if (err != NULL)
		ft_putendl_fd(err, 2);
}

void	syntax_error_msg(char *err, char *msg)
{
	ft_putstr_fd("ppsh: ", 2);
	if (err != NULL)
	{
		ft_putstr_fd("err", 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}
