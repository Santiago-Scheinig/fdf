/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:52:46 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 21:21:13 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_translate(char *str, const char *base)
{
	int	base_lenght;
	int	ans;
	int	i;
	int	index;

	i = -1;
	ans = 0;
	base_lenght = ft_strlen(base);
	while (str[++i])
	{
		index = -1;
		while (base[++index])
			if (base[index] == str[i])
				break ;
		ans = (ans * base_lenght) + index;
	}
	return (ans);
}

/**
 * Finds the first number on a STRING following the specified base.
 * @param str The string where the base number is saved.
 * @param base The base in which the number must be found.
 * @return The INT found on STR following the BASE.
 * @note If str has characters not included on the base, or str doesn't
 * exists, returns 0.
 */
int	ft_atoi_base(char *str, const char *base)
{
	char	*tmp;
	int		ans;

	ans = 0;
	if (!str)
		return (ans);
	tmp = ft_strtrim(str, base);
	if (!tmp || tmp[0])
		ans = -1;
	if (tmp)
		free(tmp);
	if (ans < 0)
		return (++ans);
	return (ft_translate(str, base));
}
