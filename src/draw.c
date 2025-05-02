/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:39:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/02 18:19:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static int	ft_depth_color(t_vector a, t_vector b)
{
	int	a_z;
	int	b_z;

	a_z = a.axi.z;
	b_z = b.axi.z;
	if (a_z < 0)
		a_z *= -1;
	if (b_z < 0)
		b_z *= -1;
	if (a_z < b_z)
		return (b.colour);
	return (a.colour);
}

void	ft_dda_algorithm(t_fdf *fdf, t_vector a, t_vector b, int color)
{
	t_fpair		d;
	t_fpair		pxl;
	float		index;
	float		step;

	d.x = b.axi.x - a.axi.x;
	d.y = b.axi.y - a.axi.y;
	if (fabsf(d.x) >= fabsf(d.y))
		step = fabsf(d.x);
	else
		step = fabsf(d.y);
	d.x = d.x / step;
	d.y = d.y / step;
	pxl.x = a.axi.x;
	pxl.y = a.axi.y;
	index = -1;
	while (++index <= step)
	{
		if ((pxl.x >= 0 && pxl.x < (int) fdf->map->width) 
		&& (pxl.y >= 0 && pxl.y < (int) fdf->map->height))
			mlx_put_pixel(fdf->map, pxl.x, pxl.y, color);
		pxl.x += d.x;
		pxl.y += d.y;
	}
}

void	ft_draw_image(t_fdf *fdf, t_projection ft_view)
{
	t_axi_xyz	axi;
	t_vector	p1;
	t_vector	p2;
	int			color;

	ft_draw_background(fdf->map, 0x000000);
 	axi.y = -1;
	while (++axi.y < fdf->plane.height)
	{
		axi.x = -1;
		while (++axi.x < fdf->plane.widht)
		{
			p1 = ft_plane_shift(fdf, fdf->plane.basis[axi.y][axi.x], ft_view);
			if ((axi.y + 1) < fdf->plane.height)
			{
				p2 = ft_plane_shift(fdf, fdf->plane.basis[axi.y + 1][axi.x], ft_view);
				color = ft_depth_color(fdf->plane.basis[axi.y + 1][axi.x], fdf->plane.basis[axi.y][axi.x]);
				ft_dda_algorithm(fdf, p1, p2, color);
			}
 			if ((axi.x + 1) < fdf->plane.widht)
			{
				p2 = ft_plane_shift(fdf, fdf->plane.basis[axi.y][axi.x + 1], ft_view);
				color = ft_depth_color(fdf->plane.basis[axi.y][axi.x + 1], fdf->plane.basis[axi.y][axi.x]);
				ft_dda_algorithm(fdf, p1, p2, color);
			}
		}
	}
	mlx_image_to_window(fdf->window, fdf->map, 0, 0);
	mlx_key_hook(fdf->window, &ft_keyhook_camera, fdf);
	mlx_scroll_hook(fdf->window, &ft_scrollhook_zoom, fdf);
	mlx_loop(fdf->window);
}
