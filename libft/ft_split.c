/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 04:31:31 by donpark           #+#    #+#             */
/*   Updated: 2021/07/29 20:59:58 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_worddup(char const *s, char c)
{
	char	*word;
	size_t	w_len;

	w_len = 0;
	while (s[w_len] && s[w_len] != c)
		w_len++;
	word = (char *)ft_calloc(w_len + 1, sizeof(char));
	if (word == NULL)
		return (0);
	ft_strlcpy(word, s, w_len + 1);
	return (word);
}

static char	**ft_freeall(char **dptr)
{
	size_t	i;

	i = 0;
	while (dptr[i] != 0)
	{
		free(dptr[i]);
		i++;
	}
	free(dptr);
	return (0);
}

static int	ft_input_word(char const *s, char c, char **words, size_t w_cnt)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < w_cnt && s[j])
	{
		if (s[j] != c)
		{
			words[i++] = ft_worddup(&s[j], c);
			if (words[i - 1] == NULL)
			{
				ft_freeall(words);
				return (-1);
			}
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	w_cnt;

	if (!s)
		return (0);
	w_cnt = ft_wordcnt(s, c);
	words = (char **)ft_calloc(w_cnt + 1, sizeof(char *));
	if (words == NULL)
		return (0);
	if (ft_input_word(s, c, words, w_cnt) == -1)
		return (0);
	return (words);
}
