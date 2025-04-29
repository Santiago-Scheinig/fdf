/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/31 12:37:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_lines(char **lines)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (lines[++i])
	{
		j = -1;
		if (lines[i][++j])
			count++;
	}
	return (count);
}

/*	Reads on FD line by line until EOF and saves it in the lines argument.	*/
/*	- Returns the amount of lines read. A line with just '\n' doesn't sum 	*/
/*	to the line read count.													*/
/*	- If allocation error, returns -1.										*/
int	ft_read_file(char ***lines, int fd)
{
	char	*aux;
	char	*str;
	char	*tmp;

	aux = ft_strdup("");
	if (!aux)
		return (-1);
	str = get_next_line(fd);
	while (str)
	{
		tmp = ft_strjoin(aux, str);
		free(str);
		free(aux);
		if (!tmp)
			return (-1);
		aux = tmp;
		str = get_next_line(fd);
	}
	*(lines) = ft_split(aux, '\n');
	free(str);
	free(aux);
	return (ft_count_lines(*(lines)));
}
