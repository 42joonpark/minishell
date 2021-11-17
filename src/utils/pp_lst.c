/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:28:00 by donpark           #+#    #+#             */
/*   Updated: 2021/11/17 15:10:30 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*pp_lstnew(char *content, int id)
{
	t_lst	*node;

	node = (t_lst *)malloc(sizeof(t_lst));
	if (node == NULL)
		return (0);
	ft_memset(node, 0, sizeof(t_lst));
	node->content = content;
	node->id = id;
	node->next = NULL;
	node->prev = NULL;
	node->space = FALSE;
	return (node);
}

void	pp_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = pp_lstlast(*lst);
		new->next = last->next;
		new->prev = last;
		new->prev->next = new;
		if (new->next != NULL)
			new->next->prev = new;
	}
}

void	pp_lstadd_front(t_lst **lst, t_lst *new)
{
	t_lst	*begin;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		begin = *lst;
		new->next = begin;
		new->prev = begin->prev;
		if (new->prev != NULL)
			new->prev->next = new;
		new->next->prev = new;
	}
}

void	pp_lstdelone(t_lst *lst)
{
	if (lst == NULL)
		return ;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	free(lst->content);
	free(lst);
}
