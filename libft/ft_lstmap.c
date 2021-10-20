/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donpark <donpark@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:52:11 by donpark           #+#    #+#             */
/*   Updated: 2021/07/07 13:41:21 by donpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*curr;
	t_list	*add_node;

	if (!lst || !f)
		return (0);
	first_node = ft_lstnew(f(lst->content));
	if (first_node == NULL)
		return (0);
	curr = first_node;
	lst = lst->next;
	while (lst)
	{
		add_node = ft_lstnew(f(lst->content));
		if (add_node == NULL)
		{
			ft_lstclear(&first_node, del);
			return (0);
		}
		curr->next = add_node;
		curr = add_node;
		lst = lst->next;
	}
	return (first_node);
}
