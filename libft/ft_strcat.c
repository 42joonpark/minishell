/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:23:26 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:23:27 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcat(char **str, char buffer[])
{
	int		idx_1;
	int		idx_2;
	char	*temp;
	char	*del;

	idx_1 = 0;
	idx_2 = 0;
	while ((*str)[idx_1])
		++idx_1;
	while (buffer[idx_2])
		++idx_2;
	temp = (char *)malloc(sizeof(char) * (idx_1 + idx_2 + 1));
	if (temp == NULL)
		return (-1);
	idx_1 = -1;
	idx_2 = -1;
	while ((*str)[++idx_1])
		temp[idx_1] = (*str)[idx_1];
	while (buffer[++idx_2])
		temp[idx_1 + idx_2] = buffer[idx_2];
	temp[idx_1 + idx_2] = '\0';
	del = *str;
	*str = temp;
	free(del);
	return (0);
}
