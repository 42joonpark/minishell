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
	return (EXIT_SUCCESS);
}
/*
int	pp_echo(t_lst *line_lst)
{
	int	option;

	option = FALSE;
	if (ft_strcmp(line_lst->content, "echo"))
		return (0);
	line_lst = line_lst->next;
	if (line_lst != NULL)
	{
		if (ft_strcmp(line_lst->content, "-n") == 0)
		{
			option = TRUE;
			line_lst = line_lst->next;
		}
		while (line_lst && (line_lst->id == ARG || line_lst->id == ENV_TYPE))
		{
			write(STDOUT_FILENO, line_lst->content, ft_strlen(line_lst->content));
			line_lst = line_lst->next;
			if (line_lst)
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (!option)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
*/
