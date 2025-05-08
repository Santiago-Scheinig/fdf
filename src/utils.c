/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:52:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/08 17:07:40 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "index.h"

/**
 * 
 *  WORKS - COULD BE IMPROVED OR MERGED?
 * 
 */
int	ft_depth_color(t_vector a, t_vector b)
{
	int		a_z;
	int		b_z;
	
	a_z = abs(a.axi.z);
	b_z = abs(b.axi.z);
	if (a_z > b_z)
		return (a.colour);
	return (b.colour);
}

/**
 * 
 * WORKS LIKE A CHARM - Not sure how tho :v
 * 
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
 * 
 * FINISHED
 * 
 */
int		ft_get_widht(t_fdf *env)
{
	t_list	*span;
	char	**y;
	int		x;
	int		widht;

	widht = 0;
	span = env->plane.span;
	while(span)
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
 * 
 * FINISHED
 * 
 */
int		ft_get_depth(t_fdf *env)
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

/**
 * 
 * WORKS - MIGHT NEED MORE IMPROVEMENT, SO FAR I'VE CODED FOR MATHS TO BE
 * DONE ONLY WHEN ACTUALLY NEDED.
 * 
 */
t_vector	ft_apply_planeshift(t_fdf *env, t_vector px)
{
	px.axi.x *= env->settings.zoom_value;
	px.axi.y *= env->settings.zoom_value;
	px.axi.z *= env->settings.zoom_value;
	if (env->settings.rotation_axi.x)
		px.axi = ft_rotate_x(px.axi, env->settings.rotation_axi.x);
	if (env->settings.rotation_axi.y)
		px.axi = ft_rotate_y(px.axi, env->settings.rotation_axi.y);
	if (env->settings.rotation_axi.z)
		px.axi = ft_rotate_z(px.axi, env->settings.rotation_axi.z);
	if (env->settings.map_projection == ISOMETRIC_PROJECTION)
		px.axi = ft_isometric_projection(px.axi);
	px.axi.x += env->settings.map_center.x;
	px.axi.y += env->settings.map_center.y;
	return (px);
}
