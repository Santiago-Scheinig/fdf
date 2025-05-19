/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:24:31 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:14:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and returns a CHAR * that includes 's'.
 */
char	*ft_strdup(const char *s)
{
	char	*str;
	int		str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, str_len + 1);
	ft_memcpy(str, s, str_len);
	return (str);
}
