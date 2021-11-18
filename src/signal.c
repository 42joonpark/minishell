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

/*
static void	handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, 0);
	if (signo == SIGINT && pid == -1) // ㅍㅕㅇ소는 부모가, 자식 있으면 자식이
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGINT) 		// 자식 있으면 부모가
		ft_putstr_fd("\n", 1);
}
*/

static void	handler(int signo)
{
	pid_t	pid;
	char	*str;

	pid = waitpid(-1, NULL, 0);
	if (signo == SIGINT && pid == -1) // ㅍㅕㅇ소는 부모가, 자식 있으면 자식이
	{
		str = ft_strdup(rl_line_buffer);
		rl_replace_line("", 0);
		ft_putstr_fd("\033[K", 1);
		ft_putstr_fd("\033[36mppsh$\033[0m ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		free(str);
	}
	else if (signo == SIGINT) 		// 자식 있으면 부모가
		ft_putstr_fd("\n", 1);
}

void	quit_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, 0);
	if (signo == SIGQUIT && pid == -1)	// 자식이 있으면 무조건 자식이
		;
	else if (signo == SIGQUIT)			// 자식이 있므녀 무조건 부모가
		ft_putendl_fd("Quit: 3", 1);
}

void	reset_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, quit_handler);
}

void	set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
