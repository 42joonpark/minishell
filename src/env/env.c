/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:22:46 by joonpark          #+#    #+#             */
/*   Updated: 2021/11/02 18:27:35 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_lst(t_lst *lst)
{
	while (lst != NULL)
	{
		write(1, lst->content, pp_strlen(lst->content));
		write(1, "\n", 1);
		lst = lst->next;
	}
}

int	pp_env(t_lst **env_lst)
{
	print_env_lst(*env_lst);
	return (EXIT_SUCCESS);
}
