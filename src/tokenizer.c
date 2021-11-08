#include "minishell.h"

int	tokenizer(t_lst **line_lst, char *line)
{
	if (parse_1(line_lst, line))	// D_QUOTE, S_QUOTE, HEREDOC, APPEND, REDIRIN, REDIROUT, PIP, ARG
		return (EXIT_FAILURE);
	if (check_1(*line_lst))			// Exception: PIP, redirect
		return (EXIT_FAILURE);
	if (parse_2(*line_lst))			// FILE_TYPE, DIR_TYPE, BUILTIN, COMMAND
		return (EXIT_FAILURE);
	parse_3(*line_lst);				// $: ENV_TYPE
	return (EXIT_SUCCESS);
}
