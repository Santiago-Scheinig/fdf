/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:39:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:05:43 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares 's1' and 's2' for 'n' bytes.
 * - Returns '0' if true, or a '+' or '-' number if false.(ASCII difference)
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_c;
	unsigned char	*s2_c;
	size_t			i;

	i = 0;
	s1_c = (unsigned char *) s1;
	s2_c = (unsigned char *) s2;
	while (i < n && s1_c[i] == s2_c[i])
		i++;
	if (i == n)
		i--;
	return ((unsigned char) s1_c[i] - (unsigned char) s2_c[i]);
}
