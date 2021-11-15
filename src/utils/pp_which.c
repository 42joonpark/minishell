#include "minishell.h"
#include <string.h>

static void	find_cmd(char *argv[], char *envs[], char **args, \
		int pipefd[2])
{
	close(pipefd[0]);
	argv[2] = args[0];
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
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
	static char			*argv[] = {WHICH_DIR, "-a", NULL, NULL};
	char				**args;
	int					pipefd[2];
	pid_t				pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		args = ft_split(command, ' ');
		find_cmd(argv, envs, args, pipefd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		read(pipefd[0], buffer, buf_size);
		buffer[ft_strlen(buffer) - 1] = '\0';
		check_newline(buffer);
	}
}
