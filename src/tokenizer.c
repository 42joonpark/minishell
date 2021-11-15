/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:43:06 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 21:22:32 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * parse_1: D_QUOTE, S_QUOTE, HEREDOC, APPEND, REDIRIN, REDIROUT, PIP, ARG
 * check_1: Exception: PIP, redirect
 * parse_2: FILE_TYPE, DIR_TYPE, BUILTIN, COMMAND
 * parse_3: $: ENV_TYPE
 */
int	tokenizer(t_lst **line_lst, char *line)
{
	if (parse_1(line_lst, line))
		return (EXIT_FAILURE);
	if (check_1(*line_lst))
		return (EXIT_FAILURE);
	if (parse_2(*line_lst))
		return (EXIT_FAILURE);
	parse_3(*line_lst);
	return (EXIT_SUCCESS);
}
