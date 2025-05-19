/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:36:37 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:03:44 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds the 'new' list to the end of the T_LIST **.
 * - If the T_LIST ** is empty, it sets 'new' at the start of it.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = ft_lstlast(*lst);
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	tmp->next = new;
}
