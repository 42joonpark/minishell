/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 06:58:40 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 13:39:05 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_minus_sign(int *n)
{
	if (*n < 0)
		return (1);
	else
		return (0);
}

static void	trans_plus(int sign, int *n)
{
	if (sign == 1)
		(*n) *= -1;
}

static size_t	ft_numlen(int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	check_minus_char(char *str, int sign)
{
	if (sign == 1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = is_minus_sign(&n);
	trans_plus(sign, &n);
	len = ft_numlen(n);
	str = (char *)ft_calloc(len + sign + 1, sizeof(char));
	if (str == NULL)
		return (0);
	str[len + sign] = '\0';
	while (len-- > 0)
	{
		str[len + sign] = n % 10 + '0';
		n /= 10;
	}
	check_minus_char(str, sign);
	return (str);
}
