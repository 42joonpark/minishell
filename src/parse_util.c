/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:41:12 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 17:37:17 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 \
	|| ft_strcmp(str, "cd") == 0 \
	|| ft_strcmp(str, "pwd") == 0 \
	|| ft_strcmp(str, "export") == 0 \
	|| ft_strcmp(str, "unset") == 0 \
	|| ft_strcmp(str, "env") == 0 \
	|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	check_id(int id)
{
	if (id == HEREDOC || id == REDIRIN || id == REDIROUT \
	|| id == APPEND || id == PIP)
		return (1);
	else
		return (0);
}

char	*exist_env(char *s)
{
	t_lst	*env_lst;
	char	*key;

	env_lst = g_data.env_lst;
	while (env_lst != NULL)
	{
		key = get_key(env_lst->content);
		if (ft_strcmp(s, key) == 0)
		{
			free(key);
			return (get_value(env_lst->content));
		}
		free(key);
		env_lst = env_lst->next;
	}
	return (NULL);
}
