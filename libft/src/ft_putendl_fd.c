/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:23:46 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:12:16 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes all of 's' into the 'fd' passed as an argument.
 * - Writes '\n' at the end, after writing 's', instead of a '\0'.
 * - Returns the amount of characters printed.
 */
int	ft_putendl_fd(char *s, int fd)
{
	int	w_bytes;

	w_bytes = ft_putstr_fd(s, fd);
	w_bytes += ft_putchar_fd('\n', fd);
	return (w_bytes);
}
