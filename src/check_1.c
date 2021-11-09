#include "minishell.h"

static int	check_syntax(t_lst *line_lst)
{
	if (line_lst->next == NULL)	// <<, >>, <, > 뒤에 NULL이 올때 Syntax error
	{
		syntax_error("ppsh: syntax error near unexpected token `newline'");
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	else if (opendir(line_lst->next->content) && (line_lst->id == REDIROUT || line_lst->id == APPEND))	// >> , > 뒤에 디렉토리가 오는경우 Syntax error (단, > 뒤에는 디렉토리가 올 수 있다)
	{
		syntax_error_msg(line_lst->next->content, "Is a directory");
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	else if (check_id(line_lst->id) && check_id(line_lst->next->id))
	{
		ft_putstr_fd("ppsh: syntax error near unexpected token", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(line_lst->next->content, 2);
		ft_putendl_fd("'", 2);
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	return (EXIT_SUCCESS);
}

int	check_1(t_lst *line_lst)
{
	int	ret;

	if (line_lst->id == PIP)	 // 처음에 파이프 문자가 나오는 경우에 대한 Syntax error
	{
		syntax_error("ppsh: syntax error near unexpected token `|'");
		g_data.exit_status = 2;
		return (EXIT_FAILURE);
	}
	while (line_lst != NULL)
	{
		if (check_id(line_lst->id))	// 현재 id가 <<, >>, <, >, | 일때
		{
			ret = check_syntax(line_lst);
			if (ret > 0)
				return (ret);
		}
		line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}
