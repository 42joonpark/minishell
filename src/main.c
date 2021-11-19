/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:35:08 by donpark           #+#    #+#             */
/*   Updated: 2021/11/19 17:36:26 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env_exp_lst(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	env_list(envp);
	put_env_index();
	exp_list();
}

void	eof_history(char *line)
{
	if (line == NULL)
	{
		ft_putstr_fd("\033[1A", 2);
		if (OS_APPLE)
			ft_putstr_fd("\033[6C", 2);
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (ft_strcmp(line, "exit") == 0)
		{
			ft_putendl_fd("exit", 2);
			free(line);
			exit(EXIT_SUCCESS);
		}
		add_history(line);
	}
}

static void	run(void)
{
	char	*line;
	t_lst	*line_lst;

	line = NULL;
	line_lst = NULL;
	while (1)
	{
		set_signal();
		line = readline("\033[36mppsh$\033[0m ");
		eof_history(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (tokenizer(&line_lst, line))
		{
			free_linelst_and_line(&line_lst, &line);
			continue ;
		}
		print_line_list(line_lst);
		execute(line_lst);
		free_linelst_and_line(&line_lst, &line);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	clear_screen();
	create_env_exp_lst(argc, argv, envp);
	init_shlvl();
	run();
	return (0);
}
