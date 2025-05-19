/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:52:46 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 13:09:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns an INT with the first number found on CHAR * in accordance
 * to the specified base.
 * @param[in] str The string where the base number is saved.
 * @param[in] base The base in which the number must be found.
 * @note If str has characters not included on the base, or str doesn't
 * exists, returns 0.
 */
int	ft_atoi_base(char *str, const char *base)
{
	char	*tmp;
	int		base_lenght;
	int		ans;
	int		i;
	int		index;

	if (!str)
		return (0);
	tmp = ft_strtrim(str, base);
	if (!tmp || tmp[0])
		return (0);
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
