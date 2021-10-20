#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	DIR	*dirp = opendir("/home/donpark/github/donpark/minishell/ex_function");
	struct dirent	*file;

	printf("d_name \t d_ino \t\t\t d_off \t d_reclen \t d_type\n");
	while ((file = readdir(dirp)) != NULL)
	{
		printf("%ld \t %ld \t %d \t %d \t\t %s \n", \
		file->d_ino, file->d_off, file->d_reclen, file->d_type, file->d_name);
	}
	closedir(dirp);
	return (0);
}
