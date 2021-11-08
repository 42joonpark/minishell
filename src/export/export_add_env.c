#include "minishell.h"

char	*key_eq_val(char *key, char *val)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(pp_strlen(key) + pp_strlen(val) + 2);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = -1;
	if (key != NULL)
		while (key[++j] != '\0')
			new_str[i++] = key[j];
	new_str[i++] = '=';
	j = -1;
	if (val != NULL)
		while (val[++j] != '\0')
			new_str[i++] = val[j];
	new_str[i] = '\0';
	return (new_str);
}

void	change_env_val(t_lst *lst, char *val)
{
	char	*tmp;
	char	*str;
	int		i;
	int		j;

	str = lst->content;
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	tmp = (char *)malloc(i + pp_strlen(val) + 2);
	if (tmp == NULL)
		return ;
	j = -1;
	while (++j < i)
		tmp[j] = lst->content[j];
	tmp[j++] = '=';
	i = 0;
	if (val != NULL)
		while (val[i] != '\0')
			tmp[j++] = val[i++];
	tmp[j] = '\0';
	free(lst->content);
	lst->content = tmp;
}

int	add_env(t_lst **env_lst, char *str)
{
	t_lst	*curr;
	t_lst	*new;

	if (str == NULL)
		return (EXIT_SUCCESS);
	curr = *env_lst;
	new = pp_lstnew(str, -1);
	if (new == NULL)
		return (EXIT_FAILURE);
	while (curr != NULL)
	{
		if (pp_strcmp_limit(curr->content, "_=", '=') == 0)
		{
			pp_lstadd_front(&curr, new);
			break ;
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}
