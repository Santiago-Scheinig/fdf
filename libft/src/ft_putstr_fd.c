/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:21:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:12:47 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Writes all of 's' into the 'fd' passed as ab argument.
 * - The '\0' character is not written at the end of 's'.
 * - Returns the amount of characters printed.
 */
int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
