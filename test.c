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

int		memory_free(char **mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = 0;
		return (1);
	}
	return (0);
}

void	double_memory_free(char **mem)
{
	int		i;

	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		mem[i] = 0;
		i++;
	}
	free(mem);
	mem = 0;
}

void	cmd_execve(char *cmd, char **env)
{
	char	**colon_split;
	char	**cmd_split;
	int		i;
	char	*slash_join;
	char	*executed_location;

	colon_split = ft_split(getenv("PATH"), ':');	// 환경변수 받아서 실행 디렉토리 별로 분리
	cmd_split = ft_split(cmd, ' ');					// cmd option 분리 (ex. echo -n)
	i = 0;
	while (colon_split[i])
	{
		slash_join = ft_strjoin(colon_split[i], "/");		// (ex. /bin → /bin/)
		executed_location = ft_strjoin(slash_join, cmd_split[0]);	// (ex. /bin/ → /bin/echo)
		memory_free(&slash_join);
		execve(executed_location, (char *const *)cmd_split, env);
		memory_free(&executed_location);
		i++;
	}
	double_memory_free(colon_split);
	double_memory_free(cmd_split);
}

int	main(int ac, char **av, char **env)
{
	/**
	 * echo		(o)
	 * cd		(x)
	 * pwd		(o)
	 * export	(x)
	 * unset	(x)
	 * env		(x)
	 */
	cmd_execve("env", env);

	return (0);
}

/*
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
			cmd_execve(&args[0]);
		}
		i++;
	}
	printf("No built in commmand");
}

void loop(t_info *info)
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
*/
