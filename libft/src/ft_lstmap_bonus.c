/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:51:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:04:48 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates a T_LIST * result of iterate 'f' on every 'lst.content'.
 * - If a node created iterating 'f' fails, it frees all the previous nodes.
 * - Returns the T_LIST * resulted of iterating 'f' on every 'lst.content'.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_lst;
	t_list	*tmp_node;
	void	*cont;

	tmp_lst = NULL;
	if (!lst || !f || !del)
		return (tmp_lst);
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
			return (ft_lstclear(&tmp_lst, del), NULL);
		tmp_node = ft_lstnew(cont);
		if (!tmp_node)
			return (del(cont), ft_lstclear(&tmp_lst, del), NULL);
		ft_lstadd_back(&tmp_lst, tmp_node);
		lst = lst->next;
	}
	return (tmp_lst);
}
