#include "minishell.h"
/*
static void	print_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		write(1, lst->content, pp_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
}
*/

int	main(int argc, char *argv[], char **envp)
{
	t_lst	*env_lst;
	t_lst	*exp_lst;

	(void)argc;
	(void)argv;
	g_data.env = envp;
	env_lst = NULL;
	exp_lst = NULL;
	env_list(&env_lst, envp);	// env를 list로 만든다.
	put_env_index(&env_lst);	// export의 정렬 순서를 env id에 입력한다.
	exp_list(&exp_lst, &env_lst);	// env_lst에 id 순서대로 출력한다.
	minishell_loop(&env_lst, &exp_lst);
	printf("main end\n"); fflush(stdout);
	return (0);
}
