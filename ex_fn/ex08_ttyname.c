#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("%s\n", ttyname(STDIN_FILENO));
	printf("%s\n", ttyname(STDOUT_FILENO));
	printf("%s\n", ttyname(STDERR_FILENO));
	return (0);
}
