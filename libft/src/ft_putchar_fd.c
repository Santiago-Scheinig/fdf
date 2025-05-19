/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:10:37 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:12:05 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes 'c' into the 'fd' passed as an argument.
 * - Returns the amount of characters printed.
 */
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
