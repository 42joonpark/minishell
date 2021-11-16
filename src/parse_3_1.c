/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:59:55 by donpark           #+#    #+#             */
/*   Updated: 2021/11/16 19:59:56 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dallor_str(char *s, int *idx)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\'')
	{
		(*idx)++;
		i++;
		if (s[i] == '?' || s[i] == '$')
			break ;
	}
	str = ft_substr(s, 0, i);
	return (str);
}

char	*remain_str(char *s, int *idx)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
	{
		(*idx)++;
		i++;
	}
	str = ft_substr(s, 0, i);
	return (str);
}
