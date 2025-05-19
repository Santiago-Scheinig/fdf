/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:59:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:03:59 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Adds the 'new' list to the start of the T_LIST ** .
 * - The previous node at the start of the T_LIST ** is moved to 'lst.next'.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = lst[0];
	lst[0] = new;
}
