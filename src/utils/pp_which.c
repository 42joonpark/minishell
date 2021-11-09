/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_find_executable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:38:56 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/21 10:51:29 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void	find_cmd(char *argv[], char *envs[], char **args,
		int pipefd[2])
{
	close(pipefd[0]);
	argv[2] = args[0];
	dup2(pipefd[1], STDOUT_FILENO);
	execve(WHICH_DIR, argv, envs);
}

void	find_executable(char *command, char *envs[], char buffer[],
		int buf_size)
{
	static char			*argv[] = {WHICH_DIR, "-a", NULL, NULL};
	char				**args;
	int					pipefd[2];
	pid_t				pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		args = pp_split(command, ' ');
		find_cmd(argv, envs, args, pipefd);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		read(pipefd[0], buffer, buf_size);
		buffer[pp_strlen(buffer) - 1] = '\0';
	}
}
