#include "minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);	// rl_line_buffer 에 있던 문장이 첫번째 인자로 보낸 text 로 대체된다.
		if (OS_APPLE)
			ft_putstr_fd("ppsh$   \n", 1);
		else
			ft_putstr_fd("\b\b  \n", 1);
		rl_on_new_line();	// 줄 바꿈을 한 후에 새 줄로 이동했다고 업데이트 루틴에 알리는 용도.
		rl_redisplay();		//rl_line_buffer 에 있는 content 를 터미널 디스플레이에 출력되도록 변경한다.
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler);	// ctrl+c 시그널에 대한 처리
	signal(SIGQUIT, SIG_IGN);	// ctrl+\ 시그널을 무시한다.
}

void	create_env_exp_lst(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	env_list(envp);		// env를 list로 만든다.
	put_env_index();	// export의 정렬 순서를 env id에 입력한다.
	exp_list();			// env_lst에 id 순서대로 정렬하여 exp_lst를 만든다.
}

void	eof_history(char *line)
{
	if (line == NULL)	// readline에서 EOF(Ctrl+d)가 들어왔을 때
	{
		ft_putstr_fd("\033[1A", 2);	// cursor line up
		if (OS_APPLE)
			ft_putstr_fd("\033[6C", 2);	// cursor right move
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (ft_strcmp(line, "exit") == 0)
		{
			ft_putendl_fd("exit", 2);
			exit(EXIT_SUCCESS);
		}
		add_history(line);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_lst	*line_lst;

	line = NULL;
	line_lst = NULL;
	clear_screen();		// 화면 초기화
	set_signal();
	create_env_exp_lst(argc, argv, envp);
	while (1)
	{
		line = readline("ppsh$ ");
		eof_history(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (tokenizer(&line_lst, line))
		{
			free_list(line_lst);
			line_lst = NULL;
			break ;
		}
<<<<<<< HEAD
		print_line_list(line_lst);	// [TEST CODE]
=======

		// print_line_list(line_lst);	// [TEST CODE]

		execute(line_lst);
>>>>>>> 67054cfc524e86d5ff79a535fd4ce1fe0e82aeef

		execute(line_lst, envp);

		free_list(line_lst);
		line_lst = NULL;
		free(line);
		line = NULL;
	}
	return (0);
}
