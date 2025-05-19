/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:30:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *	Reads on FD line by line until EOF and saves it in the lines argument.
 *	- Returns the amount of lines read. A line with just '\n' doesn't sum
 *	to the line read count.
 *	- If allocation error, returns -1.
 */
int	ft_read_file(t_list **lines, int fd)
{
	t_list	*new;
	char	*str;
	int		count;

	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		new = ft_lstnew(str);
		if (!new)
		{
			ft_lstclear(lines, free);
			return (-1);
		}
		ft_lstadd_back(lines, new);
		if (!(*lines))
		{
			ft_lstclear(lines, free);
			return (-1);
		}
		count++;
		str = get_next_line(fd);
	}
	return (count);
}
