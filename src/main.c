#include "minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);	// rl_line_buffer 에 있던 문장이 첫번째 인자로 보낸 text 로 대체된다.
		write(1, "\n", 1);
		rl_on_new_line();	// 줄 바꿈을 한 후에 새 줄로 이동했다고 업데이트 루틴에 알리는 용도.
		rl_redisplay();		//rl_line_buffer 에 있는 content 를 터미널 디스플레이에 출력되도록 변경한다.
	}
}

void	set_signal(void)
{
	signal(SIGINT, handler);	// ctrl+c 시그널에 대한 처리
	signal(SIGQUIT, SIG_IGN);	// ctrl+\ 시그널을 무시한다.
}

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	copy_env(int argc, char *argv[], char **envp)
{
	int	i;

	(void)argc;
	(void)argv;
	g_data.env = (char **)malloc(sizeof(char *) * 1024);
	i = 0;
	while (i < env_len(envp))
	{
		g_data.env[i] = pp_strdup(envp[i]);
		i++;
	}
	g_data.env[i] = NULL;
}

void	eof_history(char *line)
{
	if (line == NULL)	// readline에서 EOF(Ctrl+d)가 들어왔을 때
	{
		ft_putstr_fd("\x1b[1A", 1);	// cursor line up
		ft_putstr_fd("\033[6C", 1);	// cursor right move
		ft_putstr_fd("exit\n", 1);
		exit(1);
	}
	else
		add_history(line);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_lst	*line_lst;

	set_signal();
	copy_env(argc, argv, envp);
	while (1)
	{
		line = readline("ppsh$ ");
		eof_history(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		tokenizer(&line_lst, line);
	}
	return (0);
}
