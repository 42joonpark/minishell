/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:12:55 by donpark           #+#    #+#             */
/*   Updated: 2021/10/24 17:21:32 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pp_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	i;

	if (!s1 && !s2)
		return (0);
	else if (s1 && !s2)
		return (pp_strdup(s1));
	else if (!s1 && s2)
		return (pp_strdup(s2));
	else
	{
		strjoin = (char *)malloc(pp_strlen(s1) + pp_strlen(s2) + 1);
		if (strjoin == NULL)
			return (0);
		i = 0;
		while (*s1)
			strjoin[i++] = *(s1++);
		while (*s2)
			strjoin[i++] = *(s2++);
		strjoin[i] = '\0';
	}
	return (strjoin);
}
