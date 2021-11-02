#include "minishell.h"
#include "types.h"

int	pipe_count(t_list *line_lst)
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

int	cmd_count(t_list *line_lst)
{
	int	cnt;

	cnt = 0;
	while (line_lst != NULL)
	{
		if (line_lst->id == COMMAND || line_lst->id == BUILTIN)
			cnt++;
		line_lst = line_lst->next;
	}
	return (cnt);
}

char	*cmd_arg_join(t_list **line_lst)
{
	char	*join;
	char	*tmp1;
	char	*tmp2;

	while (*line_lst != NULL)
	{
		if ((*line_lst)->id != PIP \
		|| (*line_lst)->id != REDIRIN || (*line_lst)->id != REDIROUT \
		|| (*line_lst)->id != HEREDOC || (*line_lst)->id != APPEND \
		|| (*line_lst)->id != DIR_TYPE || (*line_lst)->id != FILE_TYPE)
		{
			if ((*line_lst)->id == BUILTIN || (*line_lst)->id == COMMAND)
				join = pp_strdup((*line_lst)->content);
			else
			{
				tmp1 = join;
				join = pp_strjoin(tmp1, " ");
				free(tmp1);
				tmp2 = join;
				join = pp_strjoin(tmp2, (*line_lst)->content);
				free(tmp2);
			}
		}
		(*line_lst) = (*line_lst)->next;
	}
	return (join);
}

void	exec(void)
{
	char	**cmd_args = pp_split(g_data.cmd_arg, ' ');
	char	cmd_locate[P_BUFFER_SIZE];

	find_executable(cmd_args[0], g_data.env, cmd_locate, P_BUFFER_SIZE);
	execve(cmd_locate, cmd_args, g_data.env);
}

// cmd1 | cmd2 | cmd3 | cmd4 | cmd5 | cmd6
void	execute(t_list *line_lst)
{
	pid_t	pid;

	g_data.pip_cnt = pipe_count(line_lst);
	g_data.cmd_cnt = cmd_count(line_lst);
	g_data.curr_cmd = 0;
	while (line_lst != NULL)
	{

		if (g_data.pip_cnt > 0)
			pipe(g_data.a);

		if (line_lst->id == BUILTIN || line_lst->id == COMMAND)
		{
			g_data.cmd_arg = cmd_arg_join(&line_lst);
			g_data.curr_cmd++;
		}
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			if (line_lst != NULL && line_lst->id == PIP)
			{
				if (g_data.curr_cmd % 2 == 0)
				{
					dup2(g_data.a[READ], STDIN_FILENO);
					dup2(g_data.b[WRITE], STDOUT_FILENO);
				}
				else
				{
					dup2(g_data.b[READ], STDIN_FILENO);
					dup2(g_data.a[WRITE], STDOUT_FILENO);
				}
			}
			exec();
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (g_data.curr_cmd % 2 == 0)
			{
				close(g_data.b[WRITE]);
				close(g_data.a[READ]);
			}
			else
			{
				close(g_data.a[WRITE]);
				close(g_data.b[READ]);
			}
			waitpid(pid, NULL, 0);
			if (line_lst != NULL)
				line_lst = line_lst->next;
		}
	}
}
