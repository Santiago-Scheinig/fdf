/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:54:33 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:04:19 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Free 'lst.content' with 'del' function. Then it frees lst.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst->content != NULL)
		del(lst->content);
	free(lst);
}
