#include "minishell.h"

void	connect_pipe(int fd[], int io)
{
	dup2(fd[io], io);
	close(fd[io]);
	// close(fd[WRITE]);
}

void	close_pipe(int fd[])
{
	close(fd[READ]);
	close(fd[WRITE]);
}

int	pipe_count(t_lst *line_lst)
{
	int	cnt;

	cnt = 0;
	while (line_lst != NULL)
	{
		if (line_lst->id == PIP)
			cnt++;
		line_lst = line_lst->next;
	}
	return (cnt);
}
