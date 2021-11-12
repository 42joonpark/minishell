/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: joonpark <joonpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:38:56 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/10 17:13:02 by joonpark         ###   ########.fr       */
=======
/*   By: donpark <donpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:38:56 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/10 16:30:56 by donpark          ###   ########.fr       */
>>>>>>> 67054cfc524e86d5ff79a535fd4ce1fe0e82aeef
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void	find_cmd(char *argv[], char *envs[], char **args, \
		int pipefd[2])
{
	close(pipefd[0]);
	argv[2] = args[0];
	dup2(pipefd[1], STDOUT_FILENO);
	execve(WHICH_DIR, argv, envs);
}

static void check_newline(char buffer[])
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			break ;
		}
		i++;
	}
}

void	find_executable(char *command, char *envs[], char buffer[], \
		int buf_size)
{
	static char			*argv[] = {WHICH_DIR, "-a", NULL};
	char				**args;
	int					pipefd[2];
	pid_t				pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split(command, ' ');
		find_cmd(argv, envs, args, pipefd);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		read(pipefd[0], buffer, buf_size);
		buffer[ft_strlen(buffer) - 1] = '\0';
<<<<<<< HEAD
=======
		check_newline(buffer);
>>>>>>> 67054cfc524e86d5ff79a535fd4ce1fe0e82aeef
	}
}
