/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:38:17 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 13:22:39 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *line, char quote, int *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == quote)
			return (EXIT_SUCCESS);
		(*i)++;
	}
	token_error("ppsh: syntax error near unexpected token", quote);
	g_data.exit_status = 2;
	return (EXIT_FAILURE);
}

static int	add_quote_str(t_lst **line_lst, char *line, int *i)
{
	char	quote;
	int		tmp;
	char	*str;

	quote = line[(*i)++];
	tmp = *i;
	if (check_quotes(line, quote, i))
		return (EXIT_FAILURE);
	if ((*i - tmp) != 0)
	{
		str = ft_substr(line, tmp, *i - tmp);
		if (quote == '"')
			pp_lstadd_back(line_lst, pp_lstnew(str, D_QUOTE));
		else
			pp_lstadd_back(line_lst, pp_lstnew(str, S_QUOTE));
	}
	return (EXIT_SUCCESS);
}

static void	add_redir_pipe(t_lst **line_lst, char *line, int *i)
{
	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		(*i)++;
		pp_lstadd_back(line_lst, pp_lstnew(ft_strdup("<<"), HEREDOC));
	}
	else if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		(*i)++;
		pp_lstadd_back(line_lst, pp_lstnew(ft_strdup(">>"), APPEND));
	}
	else if (line[*i] == '<')
		pp_lstadd_back(line_lst, pp_lstnew(ft_strdup("<"), REDIRIN));
	else if (line[*i] == '>')
		pp_lstadd_back(line_lst, pp_lstnew(ft_strdup(">"), REDIROUT));
	else if (line[*i] == '|')
		pp_lstadd_back(line_lst, pp_lstnew(ft_strdup("|"), PIP));
}

static void	add_arg(t_lst **line_lst, char *line, int *i)
{
	char	*str;
	int		tmp;

	tmp = *i;
	while (line[*i] != '\0')
	{
		if (line[*i] == ' ' || line[*i] == '\\' || line[*i] == ';' \
		|| line[*i] == '"' || line[*i] == '\'' \
		|| line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
			break ;
		(*i)++;
	}
	if ((*i - tmp) != 0)
	{
		str = ft_substr(line, tmp, (*i) - tmp);
		pp_lstadd_back(line_lst, pp_lstnew(str, ARG));
	}
	(*i)--;
}

int	parse_1(t_lst **line_lst, char *line)
{
	int	i;

	i = 0;
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
		else if (line[i] == '"' || line[i] == '\'')
		{
			if (add_quote_str(line_lst, line, &i))
				return (EXIT_FAILURE);
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			add_redir_pipe(line_lst, line, &i);
		else
			add_arg(line_lst, line, &i);
		i++;
	}
	return (EXIT_SUCCESS);
}
