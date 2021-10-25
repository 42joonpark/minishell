#include "minishell.h"
/*
int	main(int argc, char *argv[], char **env)
{
	argc = 0;
	argv = NULL;
	minishell_loop(env);
	return (0);
}
*/

int	main(int argc, char *argv[], char **env)
{
	t_list	*env_lst;
	t_list	*exp_lst;

	(void)argc;
	argv = NULL;
	env_lst = NULL;
	env_list(&env_lst, env);
	put_env_index(&env_lst);
	// print_lst(env_lst);
	// printf("- %d -\n", pp_lstsize(env_lst));
	// printf("=========================================================\n"); fflush(stdout);
	exp_lst = NULL;
	exp_list(&exp_lst, &env_lst);
	// print_lst(exp_lst);
	// printf("-- %d --\n", pp_lstsize(exp_lst));
	minishell_loop(&env_lst, &exp_lst);
	return (0);
}
