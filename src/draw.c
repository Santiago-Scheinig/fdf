/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:39:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 15:33:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * 
 * FINISHED
 * 
 */
static t_double_axi	ft_dda_difference(t_vector a, t_vector b, double *step)
{
	t_double_axi	d;
	t_double_axi	d_module;

	d.x = b.axi.x - a.axi.x;
	d.y = b.axi.y - a.axi.y;
	d_module.x = fabs(d.x);
	d_module.y = fabs(d.y);
	if (d_module.x >= d_module.y)
		(*step) = d_module.x;
	else
		(*step) = d_module.y;
	d.x = d.x / (*step);
	d.y = d.y / (*step);
	return (d);
}

/**
 * 
 * FINISHED
 * 
 */
void	ft_dda(t_fdf *fdf, t_vector a, t_vector b, int color)
{
	t_double_axi	d;
	t_double_axi	d_pxl;
	t_axi_xyz		i_pxl;
	double			index;
	double			step;

	d = ft_dda_difference(a, b, &step);
	d_pxl.x = a.axi.x;
	d_pxl.y = a.axi.y;
	index = -1;
	i_pxl.x = round(d_pxl.x);
	i_pxl.y = round(d_pxl.y);
	while (++index <= step)
	{
		i_pxl.x = round(d_pxl.x);
		i_pxl.y = round(d_pxl.y);
		if (!(i_pxl.x <= 0 || i_pxl.x >= (int) fdf->map->width)
			&& !(i_pxl.y <= 0 || i_pxl.y >= (int) fdf->map->height))
			mlx_put_pixel(fdf->map, i_pxl.x, i_pxl.y, color);
		d_pxl.x += d.x;
		d_pxl.y += d.y;
	}
}

/**
 * Draws a background on the MLX_IMAGE structure using the given color.
 * @param[in] img The image to draw it's background.
 * @param[in] color The background color.
 */
void	ft_draw_background(mlx_image_t *img, int color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < (int) img->width)
	{
		y = -1;
		while (++y < (int) img->height)
			mlx_put_pixel(img, x, y, color);
	}
}

/**
 * 
 *	WORKS - COULD BE MERGED WITH FT_DRAW_MAP?
 * 
 */
void	ft_draw_line(t_fdf *env, t_vector *line, t_vector *prev)
{
	t_vector	pxl_a;
	t_vector	pxl_b;
	int			i;

	i = -1;
	while (++i < env->plane.widht)
	{
		pxl_a = ft_apply_planeshift(env, line[i]);
		if (prev)
		{
			pxl_b = ft_apply_planeshift(env, prev[i]);
			ft_dda(env, pxl_a, pxl_b, ft_depth_color(line[i], prev[i]));
		}
		if (i + 1 < env->plane.widht)
		{
			pxl_b = ft_apply_planeshift(env, line[i + 1]);
			ft_dda(env, pxl_a, pxl_b, ft_depth_color(line[i], line[i + 1]));
		}
	}
}

/**
 * 
 *	WORKS - COULD BE MERGED WITH FT_DRAW_LINE?
 * 
 */
void	ft_draw_map(void *param)
{
	t_fdf		*env;
	t_list		*span;
	t_vector	*prev;

	env = (t_fdf *) param;
	ft_memset(env->map->pixels, 0, env->map->height * env->map->width * BPP);
	span = env->plane.span;
	prev = NULL;
	while (span)
	{
		ft_draw_line(env, span->content, prev);
		prev = span->content;
		span = span->next;
	}
}
