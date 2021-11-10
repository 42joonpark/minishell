#include "minishell.h"

void	print_line_list(t_lst *line_lst)
{
	char	*str;

	while (line_lst != NULL)
	{
		if (line_lst->id == APPEND)
			str = "APPEND";
		else if (line_lst->id == ARG)
			str = "ARG";
		else if (line_lst->id == BUILTIN)
			str = "BUILTIN";
		else if (line_lst->id == COMMAND)
			str = "COMMAND";
		else if (line_lst->id == DELIMITER)
			str = "DELIMITER";
		else if (line_lst->id == D_QUOTE)
			str = "D_QUOTE";
		else if (line_lst->id == DIR_TYPE)
			str = "DIR_TYPE";
		else if (line_lst->id == ENV_TYPE)
			str = "ENV_TYPE";
		else if (line_lst->id == FILE_TYPE)
			str = "FILE_TYPE";
		else if (line_lst->id == S_QUOTE)
			str = "S_QUOTE";
		else if (line_lst->id == HEREDOC)
			str = "HEREDOC";
		else if (line_lst->id == PIP)
			str = "PIP";
		else if (line_lst->id == REDIROUT)
			str = "REDIROUT";
		else if (line_lst->id == REDIRIN)
			str = "REDIRIN";

		printf("%s (%d: %s) %s %s\n", C_AQUA, line_lst->id, str, line_lst->content, C_NC); fflush(stdout);
		line_lst = line_lst->next;
	}
}

void	print_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		ft_putendl_fd(lst->content, 1);
		lst = lst->next;
	}
}

void	print_exe_cmdarg(t_exe *exe)
{
	int	i;

	i = 0;
	while (exe->cmd_arg[i] != NULL)
	{
		ft_putendl_fd(exe->cmd_arg[i], 1);
		i++;
	}
}
