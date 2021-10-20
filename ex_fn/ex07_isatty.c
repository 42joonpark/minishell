#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", isatty(STDIN_FILENO));
	printf("%d\n", isatty(STDOUT_FILENO));
	printf("%d\n", isatty(STDERR_FILENO));
	printf("%d\n", isatty(3));
	printf("%d\n", isatty(4));
	return (0);
}
