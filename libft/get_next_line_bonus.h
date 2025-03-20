/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:11:26 by root              #+#    #+#             */
/*   Updated: 2025/03/17 18:19:53 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

/* Ft_strlend returns the count of characters on 's' until a char end, not	 */
/* including the '\0'. 														 */
size_t	ft_strlend(char *str, char end);

/* In the specific case that a bit read is not included in the ASCII table,	*/
/* it will print an empty space instead.									*/
char	*ft_checkbin(char *line);

/* Returns a char * with the next line on the file descriptor given.	*/
char	*get_next_line(int fd);

#endif