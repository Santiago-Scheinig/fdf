/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:03:17 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:04:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees every node included on the T_LIST ** using 'del'.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		ft_lstdelone((*lst), del);
		(*lst) = tmp;
	}
}
