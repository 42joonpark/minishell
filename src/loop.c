#include "minishell.h"
#include "types.h"

int	check_quotes(char *line, char quote, int *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == quote)
			return (0);
		(*i)++;
	}
	syntax_error("syntax error");
	return (1);
}

int	add_quote_str(t_list **line_lst, char *line, int *i)
{
	char	quote;
	int		tmp;		// quote 다음 인덱스
	char	*str;

	quote = line[(*i)++];
	tmp = *i;
	if (check_quotes(line, quote, i))
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

void	add_redir_pipe(t_list **line_lst, char *line, int *i)
{
	char	*str;

	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		(*i)++;
		str = pp_strdup("<<");
		pp_lstadd_back(line_lst, pp_lstnew(str, HEREDOC));
	}
	else if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		(*i)++;
		str = pp_strdup(">>");
		pp_lstadd_back(line_lst, pp_lstnew(str, APPEND));
	}
	else if (line[*i] == '<')
	{
		str = pp_strdup("<");
		pp_lstadd_back(line_lst, pp_lstnew(str, REDIRIN));
	}
	else if (line[*i] == '>')
	{
		str = pp_strdup(">");
		pp_lstadd_back(line_lst, pp_lstnew(str, REDIROUT));
	}
	else if (line[*i] == '|')
	{
		str = pp_strdup("|");
		pp_lstadd_back(line_lst, pp_lstnew(str, PIP));
	}
}

void	add_arg(t_list **line_lst, char *line, int *i)
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

int	parse_line(t_list **line_lst, char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		if (line[i] == '\\' || line[i] == ';')
		{
			syntax_error("syntax_error");
			return (EXIT_FAILURE);
		}
		else if (line[i] == '"' || line[i] == '\'')
		{
			if (add_quote_str(line_lst, line, &i))
				return (EXIT_FAILURE);
		}
		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			add_redir_pipe(line_lst, line, &i);
		}
		else
		{
			add_arg(line_lst, line, &i);
		}
		i++;
	}
	// if (pp_lstsize(*line_lst) == 0)
		// Syntax error (cmd x)
	return (EXIT_SUCCESS);
}

int	is_builtin(char *str)
{
	if (pp_strcmp(str, "echo") == 0 \
	|| pp_strcmp(str, "cd") == 0 \
	|| pp_strcmp(str, "pwd") == 0 \
	|| pp_strcmp(str, "export") == 0 \
	|| pp_strcmp(str, "unset") == 0 \
	|| pp_strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	check_first_str(t_list *line_lst)
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

int	modify_arg_type(t_list *line_lst)
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
				{
					line_lst->next->id = DIR_TYPE;
				}
				else
				{
					line_lst->next->id = FILE_TYPE;
				}
			}
			if (line_lst->id == REDIRIN \
			&& line_lst->next != NULL \
			&& (line_lst->next->id = DIR_TYPE || line_lst->next->id == FILE_TYPE) \
			&& line_lst->next->next !=NULL && line_lst->next->next->id == ARG)
			{
				line_lst->next->next->id = COMMAND;
			}
			if (line_lst->id == REDIRIN \
			&& line_lst->next != NULL \
			&& (line_lst->next->id = DIR_TYPE || line_lst->next->id == FILE_TYPE) \
			&& line_lst->next->next->id != COMMAND \
			&& line_lst->prev != NULL && line_lst->prev->id == ARG)
			{
				line_lst->prev->id = COMMAND;
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

int	minishell_loop(t_list **env_lst, t_list **exp_lst)
{
	char	*line;
	int		is_running;
	t_list	*line_lst;

	// char	**args;
	(void)env_lst;
	(void)exp_lst;
	line_lst = NULL;
	is_running = TRUE;
	while (is_running)
	{
		line = readline("$ ");
		if (line != NULL)
			add_history(line);
		if (pp_strcmp(line, "\0") == 0)
		{
			free(line);
			continue ;
		}

		if (parse_line(&line_lst, line))	// 공백, ", ', <, >, <<, >>, |
		{
			free_list(line_lst);
			free(line);
			return (EXIT_FAILURE);
		}

		if (modify_arg_type(line_lst))
		{
			free_list(line_lst);
			free(line);
			return (EXIT_FAILURE);
		}

		print_line_list(line_lst);

		// args = pp_split(line, ' ');
		// if (pp_strcmp(args[0], "pwd") == 0)
		// 	pp_pwd();
		// if (pp_strcmp(args[0], "echo") == 0)
		// 	pp_echo(args);
		// if (pp_strcmp(args[0], "cd") == 0)
		// 	pp_cd(args);
		// if (pp_strcmp(args[0], "exit") == 0)
		// 	is_running = FALSE;
		// if (pp_strcmp(args[0], "env") == 0)
		// 	pp_env(env_lst);
		// if (pp_strcmp(args[0], "export") == 0)
		// 	pp_export(args, exp_lst, env_lst);
		// if (pp_strcmp(args[0], "unset") == 0)
		// 	pp_unset(args, exp_lst, env_lst);
		free_list(line_lst);
		line_lst = NULL;
		free(line);
		//free(args);
	}
	return (EXIT_SUCCESS);
}
