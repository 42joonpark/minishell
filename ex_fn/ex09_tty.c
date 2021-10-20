#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*path;

	fd = ttyslot();
	if (isatty(fd))
		printf("This is terminal device\n");
	path = ttyname(fd);
	printf("%s\n", path);
	return (0);
}
