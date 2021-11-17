/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:47:40 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 15:47:40 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	check_exit_num(const char *str)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] != '\0' && !ft_isdigit(str[i]))
		return (__LONG_MAX__);
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && !ft_isdigit(str[i]))
		return (__LONG_MAX__);
	return (sign * num);
}

void	exit_arg(t_lst **line_lst)
{
	long long	check;

	(*line_lst) = (*line_lst)->next;
	check = check_exit_num((*line_lst)->content);
	if (check > INT_MAX)
		syntax_error_msg2("exit", (*line_lst)->content, \
			"numeric argument required.");
	else
	{
		g_data.exit_status = check;
		g_data.exit = TRUE;
	}
}
