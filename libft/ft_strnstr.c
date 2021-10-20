/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 07:43:43 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 18:55:52 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	limit_range(size_t b_len, size_t l_len, size_t len, size_t *max)
{
	if (b_len > len)
		(*max) = len - l_len;
	else
		(*max) = b_len - l_len;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	max;
	size_t	b_len;
	size_t	l_len;

	i = 0;
	b_len = ft_strlen(big);
	l_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	if (b_len < l_len || l_len > len)
		return (0);
	limit_range(b_len, l_len, len, &max);
	while (i <= max)
	{
		if (ft_strncmp(&big[i], little, l_len) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
