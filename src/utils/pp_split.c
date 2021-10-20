/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:16:28 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/18 17:02:18 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	count_str(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			++s;
		if (*s && *s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
	}
	return (count);
}

static void	ft_strncpy(char *dest, const char *src, int n)
{
	while (*src && n > 0)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	*dest = '\0';
}

static char	**make_ret(char const *s, char c)
{
	char	**ret;
	size_t	tot;

	if (!s)
		return (NULL);
	tot = count_str(s, c);
	ret = (char **)malloc(sizeof(char *) * (tot + 1));
	if (!ret)
		return (NULL);
	return (ret);
}

char	**pp_split(char const *s, char c)
{
	const char	*cur;
	char		**ret;
	size_t		idx;

	ret = make_ret(s, c);
	if (!ret)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (*s != c)
		{
			cur = s;
			while (*s && *s != c)
				++s;
			ret[idx] = (char *)malloc(sizeof(char) * (s - cur + 1));
			ft_strncpy(ret[idx++], cur, (s - cur));
		}
		if (!*s)
			break ;
		++s;
	}
	ret[idx] = 0;
	return (ret);
}
