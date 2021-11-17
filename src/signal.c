/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:55:18 by donpark           #+#    #+#             */
/*   Updated: 2021/11/15 20:55:59 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, 0);
	if (signo == SIGINT && pid == -1)
	{
		rl_replace_line("", 0);
		if (OS_APPLE)
			ft_putstr_fd("\n", 1);
		else
			ft_putstr_fd("\b\b  \n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGINT)
		ft_putstr_fd("\n", 1);
}

void	set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
