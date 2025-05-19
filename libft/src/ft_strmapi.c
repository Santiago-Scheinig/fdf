/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:07:52 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:15:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Iterates the 'f' function in every character of 's'.
 * - Returns a CHAR * with the results of all the iterations in order.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
