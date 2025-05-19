/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:44:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:03:26 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Reverses the STRING found on a CHAR *.
 */
static	char	*ft_swap(char *str)
{
	char	swap;
	int		len;
	int		i;

	i = 0;
	if (str[0] == '-')
		i++;
	len = ft_strlen(str);
	while (i < len - 1)
	{
		swap = str[len - 1];
		str[len - 1] = str[i];
		str[i] = swap;
		i++;
		len--;
	}
	return (str);
}

/**
 * Allocates the exact memory needed for a CHAR *.
 */
static	char	*ft_setstr(int n, int len)
{
	char	*str;

	if (n < 0)
	{
		str = ft_calloc(len + 2, 1);
		if (!str)
			return (NULL);
		str[0] = '-';
	}
	else
	{
		str = ft_calloc(len + 1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

/**
 * Returns a dedicated CHAR * for the INT_MIN case.
 */
static	char	*ft_min(void)
{
	char	*str;

	str = ft_itoa(INT_MIN + 1);
	if (!str)
		return (NULL);
	str[ft_strlen(str) - 1]++;
	return (str);
}

/**
 * Counts the amount of digits that an INT variable has.
 */
static	int	ft_nbrlen(int n)
{
	int	count;

	n = n * 1;
	count = 1;
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/**
 * Returns a CHAR * that includes the INT passed as an argument.
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_nbrlen(n);
	if (n == INT_MIN)
		return (ft_min());
	str = ft_setstr(n, len);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		str[i++] = (n % 10) + 48;
		n /= 10;
	}
	str[i] = n + 48;
	return (ft_swap(&str[0]));
}
