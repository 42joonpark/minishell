/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:24:48 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:25:02 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_eq_val(char *key, char *val)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(key);
	if (val != NULL)
		len += ft_strlen(val);
	new_str = (char *)malloc(len + 2);
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
	char	*str;
	char	*key;
	char	*tmp;

	key = get_key(lst->content);
	str = ft_strjoin(key, "=");
	free(key);
	tmp = str;
	str = ft_strjoin(tmp, val);
	free(tmp);
	free(lst->content);
	lst->content = str;
}

int	add_env(t_lst **env_lst, char *str)
{
	t_lst	*curr;
	t_lst	*new;

	if (str == NULL)
		return (EXIT_SUCCESS);
	curr = *env_lst;
	new = pp_lstnew(ft_strdup(str), -1);
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
