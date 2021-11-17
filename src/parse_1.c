/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:38:17 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 15:49:24 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_1_helper(t_lst **line_lst, char *line, int *i)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (add_quote_str(line_lst, line, i))
			return (EXIT_FAILURE);
	}
	else if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		add_redir_pipe(line_lst, line, i);
	else
		add_arg(line_lst, line, i);
	(*i)++;
	if (line[*i] == ' ')
		pp_lstlast(*line_lst)->space = TRUE;
	return (EXIT_SUCCESS);
}

int	parse_1(t_lst **line_lst, char *line, int i)
{
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return (EXIT_SUCCESS);
		if (line[i] == '\\' || line[i] == ';')
		{
			token_error("ppsh: syntax error near unexpected token", line[i]);
			g_data.exit_status = 2;
			return (EXIT_FAILURE);
		}
		else
		{
			if (parse_1_helper(line_lst, line, &i))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
