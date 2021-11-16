/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:41:01 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 17:17:44 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*s2_exist_env(char *s2)
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

char	*dallor_str(char *s, int *idx)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\'')
	{
		(*idx)++;
		i++;
		if (s[i] == '?' || s[i] == '$')
			break ;
	}
	str = ft_substr(s, 0, i);
	return (str);
}

char	*remain_str(char *s, int *idx)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
	{
		(*idx)++;
		i++;
	}
	str = ft_substr(s, 0, i);
	return (str);
}

static void	modify_content(t_lst *line_lst)
{
	int		i;
	char	*str;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	int		flag;

	str = NULL;
	i = 0;
	while (line_lst->content[i] != '\0')
	{
		flag = FALSE;
		tmp2 = str;
		tmp1 = remain_str(&line_lst->content[i], &i);

		str = ft_strjoin(str, tmp1);
		if (tmp1 != NULL)
			free(tmp1);
		if (tmp2 != NULL)
			free(tmp2);
		if (line_lst->content[i] == '$')
		{
			i++;
			flag = TRUE;
		}
		tmp2 = str;
		tmp1 = dallor_str(&line_lst->content[i], &i);
		if (tmp1[0] != '\0' && ft_strcmp(tmp1, "?") != 0)
		{
			tmp3 = s2_exist_env(tmp1);
			if (tmp3 != NULL)
				line_lst->id = ENV_TYPE;
			str = ft_strjoin(str, tmp3);
			if (tmp1 != NULL)
				free(tmp1);
			if (tmp3 != NULL)
				free(tmp3);
			if (tmp2 != NULL)
				free(tmp2);
		}
		else
		{
			if (tmp1[0] == '\0' && flag == TRUE)
			{
				tmp3 = str;
				str = ft_strjoin(str, "$");
				if (tmp3 != NULL)
					free(tmp3);
			}
			else if (ft_strcmp(tmp1, "?") == 0)
			{
				tmp3 = str;
				tmp4 = ft_itoa(g_data.exit_status);
				str = ft_strjoin(str, tmp4);
				if (tmp3 != NULL)
					free(tmp3);
				if (tmp4 != NULL)
					free(tmp4);
			}
			if (tmp1 != NULL)
				free(tmp1);
		}
	}
	free(line_lst->content);
	line_lst->content = str;
}

void	parse_3(t_lst *line_lst)
{
	while (line_lst != NULL)
	{
		if (ft_strchr(line_lst->content, '$') != NULL \
		&& line_lst->id != S_QUOTE)
			modify_content(line_lst);
		line_lst = line_lst->next;
	}
}
