#include "minishell.h"
#include "types.h"

static int	check_first_str(t_lst *line_lst)
{
	if (line_lst->id == ARG)
	{
		if (is_builtin(line_lst->content))
			line_lst->id = BUILTIN;
		else
			line_lst->id = COMMAND;
	}
	else if (line_lst->id == PIP)
	{
		syntax_error("syntax error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	modify_arg_type(t_lst *line_lst)
{
	if (check_first_str(line_lst))
		return (EXIT_FAILURE);
	while (line_lst != NULL)
	{
		if (line_lst->id == REDIRIN || line_lst->id == REDIROUT || line_lst->id == APPEND)
		{
			if (line_lst->next != NULL && line_lst->next->id == ARG)
			{
				if (line_lst->id == REDIRIN && opendir(line_lst->next->content))
					line_lst->next->id = DIR_TYPE;
				else
					line_lst->next->id = FILE_TYPE;
			}
			if (line_lst->id == REDIRIN \
			&& line_lst->next != NULL \
			&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
			&& line_lst->next->next !=NULL && line_lst->next->next->id == ARG)
			{
				line_lst->next->next->id = COMMAND;
			}
			if (line_lst->id == REDIRIN \
			&& line_lst->next != NULL \
			&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
			&& line_lst->next->next->id != COMMAND \
			&& line_lst->prev != NULL && line_lst->prev->id == ARG)
			{
				line_lst->prev->id = COMMAND;
			}
			if (line_lst->id == REDIRIN \
			&& line_lst->prev != NULL && line_lst->prev->id == COMMAND \
			&& line_lst->next != NULL \
			&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
			&& line_lst->next->next != NULL && line_lst->next->next->id == COMMAND)
			{
				syntax_error("Syntax error\n");	// No such file or directory. (ex. cat < file cat > file2)

			}
		}
		else if (line_lst->id == HEREDOC)
		{
			if (line_lst->next != NULL)
				line_lst->next->id = DELIMITER;
		}
		else if (line_lst->id == PIP)
		{
			if (line_lst->next != NULL && line_lst->next->id == ARG)
			{
				if (is_builtin(line_lst->next->content))
					line_lst->next->id = BUILTIN;
				else
					line_lst->next->id = COMMAND;
			}
		}
		line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}
