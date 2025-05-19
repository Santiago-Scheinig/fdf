/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:43:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:16:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

/**
 * Returns a CHAR * resultant of the trimming of 'set' in 's1'.
 * - Cuts every match of 'set' from the start of 's1' until a non match.
 * - Cuts every match of 'set' from the end of 's1' until a non match.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		s1_len;
	int		i;

	i = 0;
	while (ft_istrim(s1[i], set))
		i++;
	s1_len = ft_strlen(&s1[i]);
	if (s1_len == 0)
		return (ft_strdup(""));
	while (ft_istrim(s1[s1_len + i - 1], set))
		s1_len--;
	tmp = ft_calloc(s1_len + 1, 1);
	if (!tmp)
		return (NULL);
	ft_strlcat(tmp, &s1[i], s1_len + 1);
	return (tmp);
}
