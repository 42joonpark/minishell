/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:55:18 by donpark           #+#    #+#             */
/*   Updated: 2021/11/20 17:21:25 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_2(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (signo == SIGQUIT)
		ft_putendl_fd("Quit: 3", 1);
}

void	reset_signal(void)
{
	signal(SIGINT, handler_2);
	signal(SIGQUIT, handler_2);
}

static void	handler_1(int signo)
{
	char	*str;

	if (signo == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		rl_replace_line("", 0);
		if (OS_APPLE)
		{
			ft_putstr_fd("\033[K", 1);
			ft_putstr_fd("ppsh$ ", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("\b\b  \n", 1);
		rl_on_new_line();
		rl_redisplay();
		free(str);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler_1);
	signal(SIGQUIT, SIG_IGN);
}
