#include "minishell.h"

char	*str_eq_quote_val(char *key, char *val)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *)malloc(ft_strlen(key) + ft_strlen(val) + 3);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = -1;
	if (key != NULL)
		while (key[++j] != '\0')
			new_str[i++] = key[j];
	new_str[i++] = '=';
	new_str[i++] = '\"';
	j = -1;
	if (val != NULL)
		while (val[++j] != '\0')
			new_str[i++] = val[j];
	new_str[i++] = '\"';
	new_str[i] = '\0';
	return (new_str);
}

void	change_exp_val(t_lst *lst, char *val)
{
	char	*str;
	int		i;
	int		j;

	str = lst->content;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	if (i == (int)ft_strlen(str))
		str[i++] = '=';
	str[i++] = '\"';
	j = 0;
	if (val != NULL)
		while (val[j] != '\0')
			str[i++] = val[j++];
	str[i++] = '\"';
	str[i] = '\0';
}

static void	add_exp_node(t_lst **exp_lst, t_lst *curr, t_lst *new, int *flag)
{
	while (curr != NULL)
	{
		if (pp_strcmp_limit(curr->content, new->content, '=') > 0)
		{
			if (*flag == 0)
				pp_lstadd_front(exp_lst, new);
			else
				pp_lstadd_front(&curr, new);
			break ;
		}
		if (curr->next == NULL)
		{
			pp_lstadd_back(&curr, new);
			break ;
		}
		(*flag)++;
		curr = curr->next;
	}
}

int	add_exp(t_lst **exp_lst, char *str)
{
	t_lst	*curr;
	t_lst	*new;
	int		flag;

	flag = 0;
	curr = *exp_lst;
	new = pp_lstnew(str, -1);
	if (new == NULL)
		return (EXIT_FAILURE);
	add_exp_node(exp_lst, curr, new, &flag);
	return (EXIT_SUCCESS);
}
