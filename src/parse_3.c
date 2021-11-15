#include "minishell.h"

static char *s2_exist_env(char *s2)
{
	t_lst	*env_lst;
	char	*key;
	env_lst = g_data.env_lst;
	while (env_lst != NULL)
	{
		key = get_key(env_lst->content);
		if (ft_strcmp(s2, key) == 0)
		{
			free(key);
			return (get_value(env_lst->content));
		}
		free(key);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static void modify_env_type(t_lst *line_lst, int *i)
{
	char	*s1;
	char	*s2;
	char	*tmp;

	s1 = ft_substr(line_lst->content, 0, *i);
	(*i)++;
	s2 = \
	ft_substr(&(line_lst->content[*i]), 0, ft_strlen(&(line_lst->content[*i])));
	free(line_lst->content);
	tmp = s2_exist_env(s2);
	if (tmp != NULL)
		line_lst->content = ft_strjoin(s1, tmp);
	else
		ft_strjoin("$", s2);
		line_lst->content = ft_strjoin(s1, "");
	free(s1);
	free(s2);
	if (tmp != NULL)
		free(tmp);
}

static void modify_content(t_lst *line_lst)
{
	int	 i;
	i = 0;
	while (line_lst->content[i] != '\0')
	{
		if (line_lst->content[i] == '$')
		{
			line_lst->id = ENV_TYPE;
			if (line_lst->content[i + 1] != '\0' \
			&& line_lst->content[i + 1] == '?')
			{
				line_lst->content = ft_itoa(g_data.exit_status);
				break ;
			}
			modify_env_type(line_lst, &i);
			break ;
		}
		i++;
	}
}

void	parse_3(t_lst *line_lst)
{
	print_line_list(line_lst);
	while (line_lst != NULL)
	{
		if (ft_strchr(line_lst->content, '$') != NULL && line_lst->id != S_QUOTE)
			modify_content(line_lst);
		line_lst = line_lst->next;
	}
}