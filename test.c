#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

#define BUILTIN_CMD 6	// echo, cd, pwd, export, unset, env

typedef struct s_info
{
	char	**builtin_str;
}	t_info;

void	init(t_info *info)
{

	info->builtin_str = (char **)malloc(BUILTIN_CMD * sizeof(char *) + 1);
	if (info->builtin_str == NULL)
		exit(1);
	info->builtin_str[0] = "echo";
	info->builtin_str[1] = "cd";
	info->builtin_str[2] = "pwd";
	info->builtin_str[3] = "export";
	info->builtin_str[4] = "unset";
	info->builtin_str[5] = "env";
	info->builtin_str[6] = NULL;
}

int	execute(char **args, t_info *info)
{
	int	i;
	int	ret_cmp;

	i = 0;
	while (i < BUILTIN_CMD)
	{
		ret_cmp = ft_strncmp(args[0], info->builtin_str[i], ft_strlen(info->builtin_str[i] + 1));
		if (ret_cmp == 0)
		{

		}
		i++;
	}
	printf("No built in commmand");

}

void lsh_loop(t_info *info)
{
	char *line;
	char **args;
	int status;

	status = 1;
	while (status) {
		line = readline("> ");
		args = ft_split(line, ' ');
		status = execute(args, info);

		free(line);
		free(args);
	}
}


int main(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL);
		exit(1);
	init(info);
	// Load config files, if any.

	// Run command loop.
	loop(info);

	// Perform any shutdown/cleanup.
	return (0);
}
