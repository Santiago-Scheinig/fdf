/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:39:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:53 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Performes the necesary mathematic calculations to know the diference
 * on scalation between the T_VECTOR a and T_VECTOR b.
 * @param a The first T_VECTOR to difference.
 * @param b The second T_VECTOR to difference.
 * @param step A DOUBLE * where to save the step be performed between each 
 * pixel of the line.
 * @return The difference T_AXI_XYZ point that will be added for each step.
 * @note All calculations are made with double to enchance pixel accuracy. 
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
 * Digital Differential Analyzer (DDA) Algorithm
 * Draws a line between two T_VECTORS on the map MLX_IMAGE_T.
 * @param env The main enviroment fdf structure.
 * @param a The first vector to draw from.
 * @param b The second vector to draw to.
 * @param color The color the line will have.
 * @note All calculations are made with double to enchance pixel accuracy.
 */
void	ft_dda(t_fdf *env, t_vector a, t_vector b, int color)
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
		if (!(i_pxl.x <= 0 || i_pxl.x >= (int) env->map->width)
			&& !(i_pxl.y <= 0 || i_pxl.y >= (int) env->map->height))
			mlx_put_pixel(env->map, i_pxl.x, i_pxl.y, color);
		d_pxl.x += d.x;
		d_pxl.y += d.y;
	}
}

/**
 * Draws a background on the MLX_IMAGE_T structure using the given color.
 * @param img The image to draw it's background.
 * @param color The background color.
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
 * Draws a map line defined by the current T_VECTOR and it's previous one.
 * @param env The main enviroment fdf structure.
 * @param line An array of T_VECTOR pointers that define a map line.
 * @param prev An array of T_VECTOR pointers to the previous map line,
 * if any.
 * @note The prev argument isn't obligatory, but if defined, will also
 * draw the lines needed between the both T_VECTOR pointers.
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
 * Draws the entire map on the MLX_IMAGE_T, displaying it on screen.
 * @param env The main enviroment fdf structure.
 * @note The function will first erase any previous pixels drawn on the 
 * MLX_IMAGE_T, allowing it to draw on an empty canvas.
 */
void	ft_draw_map(t_fdf *env)
{
	t_list		*span;
	t_vector	*prev;

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
