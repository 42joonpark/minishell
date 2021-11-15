#include "minishell.h"

/*
 * TODO
 * echo $PATH
 * echo $?
 */
int	pp_echo(char **args)
{
	int	option;
	int	i;

	option = FALSE;
	i = 0;
	if (args[i] != NULL && (ft_strcmp(args[i], "-n") == 0))
	{
		option = TRUE;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	g_data.exit_status = 0;
	return (EXIT_SUCCESS);
}