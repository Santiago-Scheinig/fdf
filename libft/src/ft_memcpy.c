/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:54:48 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/07 18:51:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies 'n' bytes from 'src' into 'dest', returning 'dest'.				*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (dest);
	ft_memmove(dest, src, n);
	return (dest);
}
