/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:46 by joonpark          #+#    #+#             */
/*   Updated: 2021/10/24 18:19:33 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_lst(t_list *lst)
{
	while (lst != NULL)
	{
		write(1, lst->content, pp_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
}

int	pp_env(t_list **env_lst)
{
	print_env_lst(*env_lst);
	return (EXIT_SUCCESS);
}
