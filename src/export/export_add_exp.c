/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:24:52 by donpark           #+#    #+#             */
/*   Updated: 2021/11/20 17:21:05 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_eq_quote_val(char *key, char *val)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(key);
	if (val != NULL)
		len += ft_strlen(val);
	new_str = (char *)malloc(len + 3);
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
	char	*key;
	char	*tmp;

	key = get_key(lst->content);
	str = ft_strjoin(key, "=\"");
	free(key);
	tmp = str;
	str = ft_strjoin(tmp, val);
	free(tmp);
	tmp = str;
	str = ft_strjoin(tmp, "\"");
	free(tmp);
	free(lst->content);
	lst->content = str;
}

static void	add_exp_node(t_lst **exp_lst, t_lst *curr, t_lst *new, int *flag)
{
	int	check;

	while (curr != NULL)
	{
		check = pp_strcmp_limit(curr->content, new->content, '=');
		if (check > 0)
		{
			if (*flag == 0)
			{
				pp_lstadd_front(exp_lst, new);
				*exp_lst = (*exp_lst)->prev;
			}
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
	new = pp_lstnew(ft_strdup(str), -1);
	if (new == NULL)
		return (EXIT_FAILURE);
	add_exp_node(exp_lst, curr, new, &flag);
	return (EXIT_SUCCESS);
}
