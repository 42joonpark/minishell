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

void    heredoc(t_lst *line_lst, t_exe *exe)
{
    pipe(exe->heredoc_fd);
    exe->heredoc_pid = fork();
    if (exe->heredoc_pid < 0)
        exit(EXIT_FAILURE);
    else if (exe->heredoc_pid == 0)
    {
        close(exe->heredoc_fd[READ]);
        ft_putstr_fd("> ", 1);
        while (get_next_line(STDIN_FILENO, &(exe->heredoc_buf)) != 0)
        {
            if (ft_strcmp(exe->heredoc_buf, line_lst->content) == 0)
                break ;
            ft_putstr_fd("> ", 1);
            ft_putendl_fd(exe->heredoc_buf, exe->heredoc_fd[WRITE]);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        connect_pipe(exe->heredoc_fd, STDIN_FILENO);
        waitpid(exe->heredoc_pid, &(exe->heredoc_status), 0);
    }
}

void	redirect_connect(t_lst *line_lst, t_exe *exe)
{
	while (line_lst != NULL && line_lst->id != PIP)
	{
		if (line_lst->id == REDIRIN)
			redirect_in(line_lst->next->content, exe);
		else if (line_lst->id == REDIROUT)
			redirect_out(line_lst->next->content, exe);
		else if (line_lst->id == APPEND)
			redirect_append(line_lst->next->content, exe);
		else if (line_lst->id == HEREDOC)
			heredoc(line_lst->next, exe);
		line_lst = line_lst->next;
	}
}