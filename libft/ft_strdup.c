/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 01:16:07 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 18:56:22 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}
