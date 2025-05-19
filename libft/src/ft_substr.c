/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:53:07 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:16:16 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns a new CHAR * with 'len' bytes copied from 's[start]'.
 * - If start > s_len, it returns a new CHAR * with 1 '\0' byte allocated.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
