#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

void	handler(int signum)
{
	// printf("signum: %d\n", signum);
	write(STDOUT_FILENO, "\twrite from signal\n", 19);
}

int	main(void)
{
	int	i;

	signal(SIGINT, handler);	// SIGINT → 'ctrl + c'
	i = 0;
	while (1)
	{
		printf("%d\n", i);
		i++;
		sleep(1);
	}
	return (0);
}
