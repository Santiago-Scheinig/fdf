/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:48:27 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:15:45 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns a CHAR * to the first match of all 'little' in 'big'.
 * - The match must exist in 'len' bytes of 'big'.
 * - Returns 'big' if 'little' is empty.
 * - Returns NULL if no match is found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		little_len;

	if (!big)
		return (NULL);
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *) big);
	i = 0;
	while (i < len)
	{
		if (!big[i])
			return (NULL);
		if (big[i] == little[0] && len >= little_len + i)
		{
			if (ft_strncmp(&big[i], &little[0], little_len) == 0)
				return ((char *) &big[i]);
		}
		i++;
	}
	return (NULL);
}
