#include "minishell.h"

static void	check_first_lstcontent(t_lst *line_lst)
{
	if (!check_id(line_lst->id))
	{
		if (is_builtin(line_lst->content))
			line_lst->id = BUILTIN;
		else
			line_lst->id = COMMAND;
	}
}

static void	check_file_dir_delimiter(t_lst *line_lst)
{
	if (line_lst->id == REDIRIN || line_lst->id == REDIROUT || line_lst->id == APPEND)	// <, >, >> 다음은 FILE_TYPE이지만 < 뒤에 디렉토리의 경우도 있음.
	{
		if (line_lst->next != NULL)
		{
			if (line_lst->id == REDIRIN && opendir(line_lst->next->content))
				line_lst->next->id = DIR_TYPE;
			else
				line_lst->next->id = FILE_TYPE;
		}
	}
	else if (line_lst->id == HEREDOC)	// << 뒤에는 DELIMITER
	{
		if (line_lst->next != NULL)
			line_lst->next->id = DELIMITER;
	}
}

static void check_file_dir_delimiter_pip(t_lst *line_lst)
{
	while (line_lst != NULL)
	{
		check_file_dir_delimiter(line_lst);
		if (line_lst->id == PIP)	// | 뒤에 id가 ARG이면 BUILTIN, CMD 타입으로 변경
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
}

static void check_command(t_lst *line_lst)
{
	while (line_lst != NULL)
	{
		if (line_lst->id == REDIRIN && line_lst->next != NULL \
		&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
		&& line_lst->next->next != NULL && !check_id(line_lst->next->next->id))
		{
			if (is_builtin(line_lst->next->next->content))
				line_lst->next->next->id = BUILTIN;
			else
				line_lst->next->next->id = COMMAND;
		}
		else if (line_lst->id == REDIRIN && line_lst->next != NULL \
		&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
		&& (line_lst->next->next->id != BUILTIN || line_lst->next->next->id != COMMAND) \
		&& line_lst->prev != NULL && !check_id(line_lst->prev->id))
		{
			if (is_builtin(line_lst->prev->content))
				line_lst->prev->id = BUILTIN;
			else
				line_lst->prev->id = COMMAND;
		}
		line_lst = line_lst->next;
	}
}

int	parse_2(t_lst *line_lst)
{
	check_first_lstcontent(line_lst);
	check_file_dir_delimiter_pip(line_lst);
	check_command(line_lst);
	return (EXIT_SUCCESS);
}
