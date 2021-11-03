#include "minishell.h"

int	check_id(int id)
{
	if (id == HEREDOC || id == REDIRIN || id == REDIROUT \
	|| id == APPEND || id == PIP)
		return (1);
	else
		return (0);
}

int	check_syntax(t_lst *line_lst)
{
	if (line_lst->next == NULL)
	{
		syntax_error("ppsh: syntax error near unexpected token `newline'");
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	else if (opendir(line_lst->next->content) && line_lst->id != REDIRIN)	// << , >> , > , | 뒤에 디렉토리가 오는경우
	{

	}
}

int	check_1(t_lst *line_lst)
{
	int	ret;

	if (line_lst->id == PIP)
	{
		syntax_error("ppsh: syntax error near unexpected token `|'");
		g_data.exit_status = 2;
		return (EXIT_FAILURE);
	}
	while (line_lst != NULL)
	{
		if (check_id(line_lst->id))
		{
			ret = check_syntax(line_lst);
			if (ret > 0)
				return (ret);
		}
		line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	tokenizer(t_lst **line_lst, char *line)
{
	if (parse_1(line_lst, line))	// D_QUOTE, S_QUOTE, HEREDOC, APPEND, REDIRIN, REDIROUT, PIP, ARG
		return (EXIT_FAILURE);
	if (check_1(*line_lst))		// PIP, redirect
		return (EXIT_FAILURE);

}
