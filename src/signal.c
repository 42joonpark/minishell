/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:55:18 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 01:15:43 by donpark          ###   ########.fr       */
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
		rl_on_new_line();
		if (OS_APPLE)
			ft_putstr_fd("\033[36mppsh$\033[0m \n", 1);
		else
			ft_putstr_fd("\b\b  \n", 1);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
