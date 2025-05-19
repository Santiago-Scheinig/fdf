/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:26:08 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:14:47 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies 'size' bytes form 'src' into 'dst'.
 * - If 'size' >= src_len + 1, it copies all of 'src' into 'dst'.
 * - Else, it truncates the copy after size - 1 bytes.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size >= src_len + 1)
		ft_memmove(dst, src, src_len + 1);
	else if (size != 0)
	{
		ft_memmove(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}
