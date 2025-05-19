/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:49:41 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:13:51 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns the amount of words found in 's' separated with 'c'.
 */
static	int	ft_wrdcount(char const *s, char c)
{
	char	*tmp;
	int		count;

	count = 0;
	if (c == 0)
		return (1);
	if (s[0] == 0)
		return (0);
	if (s[0] != c)
		count++;
	tmp = ft_strchr(s, c);
	if (tmp != NULL && tmp[1])
		count += ft_wrdcount(&tmp[1], c);
	return (count);
}

/**
 * Returns the lenght of a word, using 'c' as the end character.
 */
static	int	ft_wrdlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

/**
 * Frees every pointer inside 'wrdstr', then it frees 'wrdstr'.
 */
static	void	ft_memfree(char **wrdstr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(wrdstr[i]);
		i++;
	}
	free(wrdstr);
}

/**
 * Returns an ARRAY of CHAR * with every word found in 's'.
 * - The words are divided using 'c'.
 */
char	**ft_split(char const *s, char c)
{
	char	**wrdstr;
	int		w;
	int		i;

	if (!s)
		return (NULL);
	if (s[0] == 0)
		return (ft_calloc(1, sizeof(char *)));
	i = 0;
	w = ft_wrdcount(s, c);
	wrdstr = (char **) malloc((w + 1) * sizeof(char *));
	if (!wrdstr)
		return (NULL);
	while (i < w)
	{
		while (s[0] == c)
			s = ft_strchr(s, c) + 1;
		wrdstr[i] = ft_substr(s, 0, ft_wrdlen(s, c));
		if (!wrdstr[i])
			return (ft_memfree(wrdstr, i), NULL);
		s = ft_strchr(s, c) + 1;
		i++;
	}
	wrdstr[i] = (void *)(0);
	return (wrdstr);
}
