#include "minishell.h"
#include "types.h"

int	minishell_loop(t_list **env_lst, t_list **exp_lst)
{
	char	*line;
	int		is_running;
	t_list	*line_lst;

	// char	**args;
	(void)env_lst;
	(void)exp_lst;
	line_lst = NULL;
	is_running = TRUE;
	while (is_running)
	{
		line = readline("$ ");
		if (line != NULL)
			add_history(line);
		if (pp_strcmp(line, "\0") == 0)
		{
			free(line);
			continue ;
		}

		if (parse_line(&line_lst, line))	// 공백, ", ', <, >, <<, >>, |
		{
			free_list(line_lst);
			free(line);
			return (EXIT_FAILURE);
		}

		if (modify_arg_type(line_lst))	// cmd, file, dir, delimiter
		{
			free_list(line_lst);
			free(line);
			return (EXIT_FAILURE);
		}

		check_dollar(line_lst, *env_lst);

		// line_lst 의 content와 type 확인
		print_line_list(line_lst);


		// args = pp_split(line, ' ');
		// if (pp_strcmp(args[0], "pwd") == 0)
		// 	pp_pwd();
		// if (pp_strcmp(args[0], "echo") == 0)
		// 	pp_echo(args);
		// if (pp_strcmp(args[0], "cd") == 0)
		// 	pp_cd(args);
		// if (pp_strcmp(args[0], "exit") == 0)
		// 	is_running = FALSE;
		// if (pp_strcmp(args[0], "env") == 0)
		// 	pp_env(env_lst);
		// if (pp_strcmp(args[0], "export") == 0)
		// 	pp_export(args, exp_lst, env_lst);
		// if (pp_strcmp(args[0], "unset") == 0)
		// 	pp_unset(args, exp_lst, env_lst);
		free_list(line_lst);
		line_lst = NULL;
		free(line);
		//free(args);
	}
	return (EXIT_SUCCESS);
}
