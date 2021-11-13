/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonpark <joonpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:53:48 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/13 17:40:02 by joonpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_lst *lst)
{
	t_lst	*tmp;

	tmp = NULL;
	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = NULL;
		lst = tmp;
	}
}

void	exe_free(t_exe *exe)
{
	int	idx;
	
	idx = 0;
	if (exe->cmd_arg != NULL)
	{
		while (exe->cmd_arg[idx] != NULL)
			free(exe->cmd_arg[idx++]);
		free(exe->cmd_arg);
	}
	free(exe);
	exe = NULL;
}

int	free_args(char **args)
{
	size_t	idx;

	idx = 0;
	while (args[idx] != NULL)
	{
		free(args[idx]);
		++idx;
	}
	free(args);
	return (EXIT_SUCCESS);
}