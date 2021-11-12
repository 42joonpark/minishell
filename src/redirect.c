#include "minishell.h"

int	redirect_in(char *file, t_exe *exe)
{
	exe->redir_in = open(file, O_RDONLY);
	if (exe->redir_in < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_in, STDIN_FILENO);
	close(exe->redir_in);
	return (EXIT_SUCCESS);
}

int	redirect_out(char *file, t_exe *exe)
{
	exe->redir_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (exe->redir_out < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_out, STDOUT_FILENO);
	close(exe->redir_out);
	return (EXIT_SUCCESS);
}

int	redirect_append(char *file, t_exe *exe)
{
	exe->redir_out = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (exe->redir_out < 0)
	{
		syntax_error_msg(file, strerror(errno));
		g_data.exit_status = 1;
		return (g_data.exit_status);
	}
	dup2(exe->redir_out, STDOUT_FILENO);
	close(exe->redir_out);
	return (EXIT_SUCCESS);
}
