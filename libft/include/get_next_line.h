/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:11:26 by root              #+#    #+#             */
/*   Updated: 2025/05/19 16:50:57 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include "libft.h"

/**
 * Ft_strlend returns the count of characters on 's' until a char end, not
 * including the '\0'.
 */
size_t	ft_strlend(char *str, char end);

/**
 * In the specific case that a bit read is not included in the ASCII table,
 * it will print an empty space instead.
 */
char	*ft_checkbin(char *line);

/**
 * Returns a char * with the next line on the file descriptor given.
 */
char	*get_next_line(int fd);

#endif