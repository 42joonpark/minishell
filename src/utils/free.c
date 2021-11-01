/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:53:48 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/01 11:18:55 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_list(t_list *lst)
{
	t_list	*tmp;

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
