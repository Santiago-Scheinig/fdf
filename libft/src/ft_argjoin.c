/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:00:22 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and returns a CHAR * that includes every content included in the
 * arguments **ARGV, but as a single string instead.
 */
char	*ft_argjoin(char **argv)
{
	char	*str;
	int		i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (argv[++i])
		str_len += ft_strlen(argv[i]);
	str_len += i;
	str = ft_calloc(str_len + 1, sizeof(char));
	i = 0;
	while (argv[++i])
	{
		ft_strlcat(str, argv[i], str_len);
		ft_strlcat(str, " ", str_len);
	}
	return (str);
}
