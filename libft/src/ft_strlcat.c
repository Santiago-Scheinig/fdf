/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:16:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:14:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Concatenates 'size' bytes from 'src' at the end of 'dst'.
 * - If 'size' <= dst_len, it doesn't concatenate.
 * - If 'size' >= dst_len + src_len + 1, it concatenates all of 'src'.
 * - Else, it truncates the concatenation after 'size' - 1 bytes.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size >= dst_len + src_len + 1)
		ft_memmove(&dst[dst_len], src, src_len + 1);
	else if (size != 0 && size > dst_len + 1)
	{
		ft_memmove(&dst[dst_len], src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	else if (size <= dst_len)
		return (size + src_len);
	return (dst_len + src_len);
}
