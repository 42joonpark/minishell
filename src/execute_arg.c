#include "minishell.h"

static int	check_arg(t_lst *line_lst)
{
	int	cnt;

	cnt = 0;
	while (line_lst != NULL && line_lst->id != PIP)
	{
		if (line_lst->id == ARG || line_lst->id == D_QUOTE \
			|| line_lst->id == S_QUOTE || line_lst->id == ENV_TYPE)
			cnt++;
		line_lst = line_lst->next;
	}
	return (cnt);
}

static void	command_arg_helper(t_lst **line_lst, t_exe *exe, int *i)
{
	while ((*line_lst) != NULL && (*line_lst)->id != PIP)
	{
		if ((*line_lst)->id == ARG || (*line_lst)->id == D_QUOTE \
			|| (*line_lst)->id == S_QUOTE || (*line_lst)->id == ENV_TYPE)
		{
			exe->cmd_arg[(*i)++] = ft_strdup((*line_lst)->content);
		}
		(*line_lst) = (*line_lst)->next;
	}
}

void	command_arg(t_lst **line_lst, t_exe *exe)
{
	int	arg_cnt;
	int	i;

	while ((*line_lst) != NULL && (*line_lst)->id != PIP)
	{
		if ((*line_lst)->id == COMMAND || (*line_lst)->id == BUILTIN)
		{
			arg_cnt = check_arg((*line_lst));
			exe->cmd_arg = (char **)malloc(sizeof(char *) * (arg_cnt + 2));
			exe->cmd_arg[0] = ft_strdup((*line_lst)->content);
			exe->cmd_arg[arg_cnt + 1] = NULL;
			(*line_lst) = (*line_lst)->next;
			i = 1;
			command_arg_helper(line_lst, exe, &i);
			break ;
		}
		if ((*line_lst) != NULL)
			(*line_lst) = (*line_lst)->next;
	}
}