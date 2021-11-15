#include "minishell.h"

void	syntax_error(char *err)
{
	if (err != NULL)
		ft_putendl_fd(err, 2);
}

void	syntax_token_error(char *err, char token)
{
	ft_putstr_fd(err, 2);
	ft_putstr_fd(" `", 2);
	write(2, &token, 1);
	ft_putendl_fd("'", 2);
}

void	syntax_error_msg(char *err, char *msg)
{
	ft_putstr_fd("ppsh: ", 2);
	if (err != NULL)
	{
		ft_putstr_fd(err, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	syntax_error_msg2(char *err1, char *err2, char *msg)
{
	ft_putstr_fd("ppsh: ", 2);
	if (err1 != NULL)
	{
		ft_putstr_fd(err1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err2 != NULL)
	{
		ft_putstr_fd(err2, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}