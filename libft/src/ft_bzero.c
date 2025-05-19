/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:01:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sets 'n' bytes of the VOID * passed as an argument, to '\0'.
 */
void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, '\0', n);
}
