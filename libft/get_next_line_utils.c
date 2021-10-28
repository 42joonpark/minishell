/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 03:27:43 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 18:56:53 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_cut_idx(char *str, int *cut_idx)
{
	(*cut_idx) = is_newline(str);
	if (*cut_idx != -1)
		return (1);
	else
		return (0);
}

int	is_read_size(int *read_size, int fd, char **buf)
{
	(*read_size) = read(fd, *buf, BUFFER_SIZE);
	if ((*read_size) > 0)
		return (1);
	else
		return (0);
}
