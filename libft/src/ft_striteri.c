/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:53:51 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:14:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Iterates 'f' in every character of 's'.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
