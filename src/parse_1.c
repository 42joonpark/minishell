#include "minishell.h"

static int	check_quotes(char *line, char quote, int *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == quote)
			return (EXIT_SUCCESS);
		(*i)++;
	}
	syntax_error("syntax error");
	return (EXIT_FAILURE);
}

static int	add_quote_str(t_lst **line_lst, char *line, int *i)
{
	char	quote;
	int		tmp;		// quote 다음 인덱스	"abcdef" -> a위치
	char	*str;

	quote = line[(*i)++];
	tmp = *i;	// tmp는 "abcdef" -> a 위치
	if (check_quotes(line, quote, i))	// i는 마지막 " 위치
		return (EXIT_FAILURE);
	if ((*i - tmp) != 0)
	{
		str = pp_substr(line, tmp, *i - tmp);
		if (quote == '"')
			pp_lstadd_back(line_lst, pp_lstnew(str, D_QUOTE));
		else
			pp_lstadd_back(line_lst, pp_lstnew(str, S_QUOTE));
	}
	return (EXIT_SUCCESS);
}

static void	add_redir_pipe(t_lst **line_lst, char *line, int *i)
{
	char	*str;

	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		(*i)++;
		pp_lstadd_back(line_lst, pp_lstnew(pp_strdup("<<"), HEREDOC));
	}
	else if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		(*i)++;
		pp_lstadd_back(line_lst, pp_lstnew(pp_strdup(">>"), APPEND));
	}
	else if (line[*i] == '<')
		pp_lstadd_back(line_lst, pp_lstnew(pp_strdup(">>"), REDIRIN));
	else if (line[*i] == '>')
		pp_lstadd_back(line_lst, pp_lstnew(pp_strdup(">"), REDIROUT));
	else if (line[*i] == '|')
		pp_lstadd_back(line_lst, pp_lstnew(pp_strdup("|"), PIP));
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
		str = pp_substr(line, tmp, (*i) - tmp);
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
		while (line[i] == ' ')
			i++;
		if (line[i] == '\\' || line[i] == ';')
		{
			syntax_error(line[i]);
			return (EXIT_FAILURE);
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			if (add_quote_str(cmd, line, &i))
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
