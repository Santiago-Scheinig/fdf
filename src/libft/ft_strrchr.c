/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:49:13 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/07 18:57:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns a CHAR * to the last ocurrance of 'c' inside 's'.				*/
/* - Return NULL in case no ocurrence is found.								*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*tmp;
	char	c_c;

	i = 0;
	c_c = (char) c;
	tmp = NULL;
	while (s[i])
	{
		if (s[i] == c_c)
			tmp = (char *) &s[i];
		i++;
	}
	if (s[i] == c_c)
		tmp = (char *) &s[i];
	return ((char *) tmp);
}
