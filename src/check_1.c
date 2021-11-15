/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:30:47 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:30:48 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(t_lst *line_lst)
{
	if (line_lst->next == NULL)
	{
		syntax_error("ppsh: syntax error near unexpected token `newline'");
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	else if (opendir(line_lst->next->content) \
	&& (line_lst->id == REDIROUT || line_lst->id == APPEND))
	{
		syntax_error_msg(line_lst->next->content, "Is a directory");
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	else if (check_id(line_lst->id) && check_id(line_lst->next->id))
	{
		ft_putstr_fd("ppsh: syntax error near unexpected token", 2);
		ft_putstr_fd("`", 2);
		ft_putstr_fd(line_lst->next->content, 2);
		ft_putendl_fd("'", 2);
		g_data.exit_status = 2;
		return (g_data.exit_status);
	}
	return (EXIT_SUCCESS);
}

int	check_1(t_lst *line_lst)
{
	int	ret;

	if (line_lst->id == PIP)
	{
		syntax_error("ppsh: syntax error near unexpected token `|'");
		g_data.exit_status = 2;
		return (EXIT_FAILURE);
	}
	while (line_lst != NULL)
	{
		if (check_id(line_lst->id))
		{
			ret = check_syntax(line_lst);
			if (ret > 0)
				return (ret);
		}
		line_lst = line_lst->next;
	}
	return (EXIT_SUCCESS);
}
