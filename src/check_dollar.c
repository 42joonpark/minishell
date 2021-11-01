#include "minishell.h"
#include "types.h"

static int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static char	*s2_exist_env(char *s2, t_list *env_lst)
{
	char	*key;

	while (env_lst != NULL)
	{
		key = get_key(env_lst->content);
		if (pp_strcmp(s2, key) == 0)
		{
			free(key);
			return (get_value(env_lst->content));
		}
		free(key);
		env_lst = env_lst->next;
	}
	return (NULL);
}

static void	modify_content(t_list *line_lst, t_list *env_lst)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*tmp;

	i = 0;
	while (line_lst->content[i] != '\0')
	{
		if (line_lst->content[i] == '$')
		{
			line_lst->id = ENV_TYPE;
			s1 = pp_substr(line_lst->content, 0, i);
			i++;
			s2 = pp_substr(&(line_lst->content[i]), 0, pp_strlen(&(line_lst->content[i])));
			free(line_lst->content);
			tmp = s2_exist_env(s2, env_lst);
			if (tmp != NULL)
				line_lst->content = pp_strjoin(s1, tmp);
			else
				line_lst->content = pp_strjoin(s1, "");
			free(s1);
			free(s2);
			if (tmp != NULL)
				free(tmp);
			break ;
		}
		i++;
	}
}

void	check_dollar(t_list *line_lst, t_list *env_lst)
{
	while (line_lst != NULL)
	{
		if (is_dollar(line_lst->content))
			modify_content(line_lst, env_lst);
		line_lst = line_lst->next;
	}
}
