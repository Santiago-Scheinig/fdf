/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:52:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Searches for the higher depth between two T_VECTOR points.
 * @param a The first T_VECTOR point.
 * @param b The second T_VECTOR point.
 * @return The color of the highest T_VECTOR point.
 */
int	ft_depth_color(t_vector a, t_vector b)
{
	int	a_z;
	int	b_z;

	a_z = abs(a.axi.z);
	b_z = abs(b.axi.z);
	if (a_z > b_z)
		return (a.colour);
	return (b.colour);
}

/**
 * Searches for the color defined on a point of the .fdf map file.
 * @param colour The STRING from where to reach the colour.
 * @param z The depth of the point which color is being saved.
 * @return The colour found.
 * @note If no color is define on the .fdf map file, a colour is assigned
 * which depends of the height passed as argument.
 */
int	ft_get_colour(char *colour, int z)
{
	int			ans;

	if (!colour)
	{
		if (z > 0)
			return (0xFFFF0000 - (0x001111 * z));
		if (z < 0)
			return (0xFF0000FF + (0x111100 * z));
		return (0xFFFFFFFF);
	}
	colour += 3;
	ans = ft_atoi_base(colour, "0123456789abcdef");
	if (!ans)
		ans = ft_atoi_base(colour, "0123456789ABCDEF");
	return (ans);
}

/**
 * Calculates the widht of the .fdf map file.
 * @param env The main fdf enviroment structure.
 */
int	ft_get_widht(t_fdf *env)
{
	t_list	*span;
	char	**y;
	int		x;
	int		widht;

	widht = 0;
	span = env->plane.span;
	while (span)
	{
		y = ft_split(span->content, ' ');
		free(span->content);
		if (!y)
			ft_forcend(env, MLX_MEMFAIL);
		x = 0;
		while (y[x])
			x++;
		if (!widht)
			widht = x;
		if (x < widht)
			widht = x;
		span->content = y;
		span = span->next;
	}
	return (widht);
}

/**
 * Calculates the depth of the .fdf map file.
 * @param env The main fdf enviroment structure.
 */
int	ft_get_depth(t_fdf *env)
{
	t_list	*span;
	char	**y;
	int		x;
	int		z;
	int		depth;

	depth = 0;
	span = env->plane.span;
	while (span)
	{
		y = span->content;
		x = -1;
		while (y[++x])
		{
			z = ft_atoi(y[x]);
			if (z < 0 && depth < (z * -1))
				depth = z;
			else if (depth < z)
				depth = z;
		}
		span = span->next;
	}
	return (depth);
}
