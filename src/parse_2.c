/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:39:56 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:58:28 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_command(t_lst *line_lst)
{
	while (line_lst != NULL)
	{
		if (line_lst->id == REDIRIN && line_lst->next != NULL \
		&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
		&& line_lst->next->next != NULL && !check_id(line_lst->next->next->id))
		{
			if (is_builtin(line_lst->next->next->content))
				line_lst->next->next->id = BUILTIN;
			else
				line_lst->next->next->id = COMMAND;
		}
		else if (line_lst->id == REDIRIN && line_lst->next != NULL \
		&& (line_lst->next->id == DIR_TYPE || line_lst->next->id == FILE_TYPE) \
		&& line_lst->next->next != NULL \
		&& (line_lst->next->next->id != BUILTIN \
		|| line_lst->next->next->id != COMMAND) \
		&& line_lst->prev != NULL && !check_id(line_lst->prev->id))
		{
			if (is_builtin(line_lst->prev->content))
				line_lst->prev->id = BUILTIN;
			else
				line_lst->prev->id = COMMAND;
		}
		line_lst = line_lst->next;
	}
}

static void	check_command_count_helper(t_lst *line_lst, int *flag)
{
	while (line_lst != NULL && line_lst->id != PIP)
	{
		while (line_lst->id != COMMAND && line_lst->id != BUILTIN)
			line_lst = line_lst->next;
		if ((line_lst->id == COMMAND || line_lst->id == BUILTIN) \
		&& (*flag) == 0)
		{
			(*flag)++;
			line_lst = line_lst->next;
		}
		while (line_lst != NULL && line_lst->id != PIP)
		{
			if ((check_id(line_lst->id) || line_lst->id == FILE_TYPE \
				|| line_lst->id == DIR_TYPE || line_lst->id == DELIMITER) \
				&& line_lst->next != NULL)
				line_lst = line_lst->next;
			else if ((*flag) != 0 && line_lst->id != S_QUOTE)
				line_lst->id = ARG;
			line_lst = line_lst->next;
		}
	}
}

static void	check_command_count(t_lst *line_lst)
{
	int	flag;

	while (line_lst != NULL)
	{
		flag = 0;
		check_command_count_helper(line_lst, &flag);
		if (flag == 0)
		{
			while (line_lst != NULL && line_lst->id != PIP)
			{
				if (line_lst->id == ARG \
				|| line_lst->id == D_QUOTE || line_lst->id == S_QUOTE)
				{
					line_lst->id = COMMAND;
					break ;
				}
				line_lst = line_lst->next;
			}
		}
		while (line_lst != NULL && line_lst->id != PIP)
			line_lst = line_lst->next;
		if (line_lst != NULL)
			line_lst = line_lst->next;
	}
}

int	parse_2(t_lst *line_lst)
{
	if (!check_id(line_lst->id))
	{
		if (is_builtin(line_lst->content))
			line_lst->id = BUILTIN;
		else
			line_lst->id = COMMAND;
	}
	check_file_dir_delimiter_pip(line_lst);
	check_command(line_lst);
	check_command_count(line_lst);
	return (EXIT_SUCCESS);
}
