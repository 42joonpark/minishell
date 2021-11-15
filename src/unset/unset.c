#include "minishell.h"

static int unset_return()
{
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}

int	pp_unset(char **args, t_lst **exp_lst, t_lst **env_lst)
{
	t_lst	*exp;
	t_lst	*env;
	t_lst	*tmp;

	if (args[1] == NULL)
		return (unset_return());
	exp = *exp_lst;
	env = *env_lst;
	while (exp != NULL)
	{
		tmp = is_same_content_key(exp_lst, args[1]);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		exp = exp->next;
	}
	while (env != NULL)
	{
		tmp = is_same_content_key(env_lst, args[1]);
		if (tmp != NULL)
			pp_lstdelone(tmp);
		env = env->next;
	}
	return (unset_return());
}
