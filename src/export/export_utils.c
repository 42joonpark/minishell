/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:22:28 by donpark           #+#    #+#             */
/*   Updated: 2021/10/25 14:22:29 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (0);
	j = 0;
	while (j < i)
	{
		tmp[j] = str[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*get_value(char *str)
{
	int		i;

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
	if (i == (int)pp_strlen(str))
		return (NULL);
	else
		return (pp_strdup(&str[i]));
}

int	is_exist_eq(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

t_list	*is_same_content_key(t_list **lst, char *key)
{
	t_list	*tmp;
	char	*content_key;

	tmp = *lst;
	while (tmp != NULL)
	{
		content_key = get_key(tmp->content);
		if (pp_strcmp(key, content_key) == 0)
		{
			free(content_key);
			return (tmp);
		}
		free(content_key);
		tmp = tmp->next;
	}
	return (NULL);
}
