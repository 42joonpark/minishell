#include "minishell.h"

void	parent_process(t_exe *exe, pid_t pid, int i)
{
	int	status;

	status = 0;
	if (i == 0 && exe->pip_cnt == 0)
	{
	}
	else if (i % 2 == 0 && exe->pip_cnt == 0)
		close(exe->b[READ]);
	else if (i % 2 != 0 && exe->pip_cnt == 0)
		close(exe->a[READ]);
	else if (i % 2 == 0 && exe->pip_cnt > 0)
	{
		close(exe->a[WRITE]);
		if (exe->flag_b != 0)
			close(exe->b[READ]);
	}
	else if (i % 2 != 0 && exe->pip_cnt > 0)
	{
		close(exe->a[READ]);
		close(exe->b[WRITE]);
	}
	waitpid(pid, &status, 0);
	if (status > 0)
		g_data.exit_status = status >> 8;
}