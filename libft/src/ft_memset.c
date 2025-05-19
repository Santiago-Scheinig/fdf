/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:02:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:06:12 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sets 'n' bytes of 's' with 'c', returning 's'.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = (unsigned char *) s;
	while (i < n)
		tmp[i++] = (unsigned char) c;
	return (s);
}
