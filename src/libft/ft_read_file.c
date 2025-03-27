/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:32:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/20 20:13:50 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Reads on FD line by line until EOF and saves it in the lines argument.	*/
/*	- Returns the amount of lines read.										*/
/*	- If allocation error, returns -1.										*/
int	ft_read_file(char ***lines, int fd)
{
	char	*aux;
	char	*str;
	char	*tmp;
	int		count;

	count = 0;
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
		count++;
		aux = tmp;
		str = get_next_line(fd);
	}
	*(lines) = ft_split(aux, '\n');
	free(str);
	free(aux);
	return (count);
}
