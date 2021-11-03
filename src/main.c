#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_lst	*env_lst;
	t_lst	*exp_lst;

	(void)argc;
	(void)argv;
	env_lst = NULL;
	exp_lst = NULL;
	env_list(&env_lst, envp);	// env를 list로 만든다.
	put_env_index(&env_lst);	// export의 정렬 순서를 env id에 입력한다.
	exp_list(&exp_lst, &env_lst);	// env_lst에 id 순서대로 정렬하여 exp_lst를 만든다.
	g_data.env = envp;

	minishell_loop(&env_lst, &exp_lst);
	return (0);
}
