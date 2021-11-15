/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:58:32 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:58:33 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_file_dir_delimiter(t_lst *line_lst)
{
	if (line_lst->id == REDIRIN || line_lst->id == REDIROUT \
	|| line_lst->id == APPEND)
	{
		if (line_lst->next != NULL)
		{
			if (line_lst->id == REDIRIN && opendir(line_lst->next->content))
				line_lst->next->id = DIR_TYPE;
			else
				line_lst->next->id = FILE_TYPE;
		}
	}
	else if (line_lst->id == HEREDOC)
	{
		if (line_lst->next != NULL)
			line_lst->next->id = DELIMITER;
	}
}

void	check_file_dir_delimiter_pip(t_lst *line_lst)
{
	while (line_lst != NULL)
	{
		check_file_dir_delimiter(line_lst);
		if (line_lst->id == PIP)
		{
			if (line_lst->next != NULL && line_lst->next->id == ARG)
			{
				if (is_builtin(line_lst->next->content))
					line_lst->next->id = BUILTIN;
				else
					line_lst->next->id = COMMAND;
			}
		}
		line_lst = line_lst->next;
	}
}
