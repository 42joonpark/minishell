/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:41:01 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 19:56:31 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_dallor(char dallor, int *i, int *flag)
{
	if (dallor == '$')
	{
		(*i)++;
		*flag = TRUE;
	}
}

static void	modify_content_1(t_lst *line_lst, char *tmp[4], char **str)
{
	tmp[1] = (*str);
	tmp[2] = exist_env(tmp[0]);
	if (tmp[2] != NULL)
		line_lst->id = ENV_TYPE;
	(*str) = ft_strjoin((*str), tmp[2]);
	free_tmp(tmp, 0);
}

static void	modify_content_2(char *tmp[4], char **str, int flag)
{
	if (tmp[0][0] == '\0' && flag == TRUE)
	{
		tmp[2] = (*str);
		(*str) = ft_strjoin((*str), "$");
	}
	else if (ft_strcmp(tmp[0], "?") == 0)
	{
		tmp[2] = (*str);
		tmp[3] = ft_itoa(g_data.exit_status);
		(*str) = ft_strjoin((*str), tmp[3]);
	}
	free_tmp(tmp, 0);
}

static void	modify_content(t_lst *line_lst)
{
	int		i;
	char	*str;
	char	*tmp[4];
	int		flag;

	str = NULL;
	i = 0;
	while (line_lst->content[i] != '\0')
	{
		free_tmp(tmp, 1);
		flag = FALSE;
		tmp[1] = str;
		tmp[0] = remain_str(&line_lst->content[i], &i);
		str = ft_strjoin(str, tmp[0]);
		free_tmp(tmp, 0);
		check_dallor(line_lst->content[i], &i, &flag);
		tmp[0] = dallor_str(&line_lst->content[i], &i);
		if (tmp[0][0] != '\0' && ft_strcmp(tmp[0], "?") != 0)
			modify_content_1(line_lst, tmp, &str);
		else
			modify_content_2(tmp, &str, flag);
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
