/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:39:50 by sscheini          #+#    #+#             */
/*   Updated: 2025/04/29 20:04:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Draws a background on the MLX_IMAGE structure using the given color.
 * @param[in] img The image to draw it's background.
 * @param[in] color The background color.
 */
static void ft_draw_background(mlx_image_t *img, int color)
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

//doesn't work
/* static void	ft_draw_line(t_fdf *fdf, t_axi_xyz p1, t_axi_xyz p2)
{
	t_axi_xyz	p3;
	t_axi_xyz	m;
	int		step;
	int		i;

	m.x = abs(p2.x - p1.x);
	m.y = abs(p2.y - p1.y);
	if (m.x >= m.y)
		step = m.x;
	else
		step = m.y;
	m.x = m.x / step;
	m.y = m.y / step;
	p3.x = p1.x;
	p3.y = p1.y;
	i = 0;
	while (++i <= step)
	{
		//ft_printf("%i\n", x);
		mlx_put_pixel(fdf->img, p3.x, p3.y, 0xFF0000);
		p3.x += m.x;
		p3.y += m.y;
	}
} */

static void	ft_draw_vector_points(t_fdf *fdf)
{
	t_axi_xyz	axi;
	t_axi_xyz	pxl;
	int			pxl_color;
	
	axi.y = -1;
	while (++axi.y < fdf->plane.height)
	{
		axi.x = -1;
		while (++axi.x < fdf->plane.widht)
		{
			pxl = fdf->plane.shift[axi.y][axi.x].axi;
			pxl.x += fdf->settings.map_center.x;
			pxl.y += fdf->settings.map_center.y;
			pxl_color = fdf->plane.basis[axi.y][axi.x].colour;
			if ((pxl.x >= 0 && pxl.x < (int) fdf->img->width) 
			&& (pxl.y >= 0 && pxl.y < (int) fdf->img->height))
				mlx_put_pixel(fdf->img, pxl.x, pxl.y, pxl_color);
		}
	}
}
//
void	ft_draw_image(t_fdf *fdf)
{
/* 	t_axi_xyz	p1;
	t_axi_xyz	p2; */

	ft_draw_background(fdf->img, 0x000000);
	if (fdf->settings.map_projection == ISOMETRIC_PROJECTION)
		ft_plane_shift(fdf, ft_isometric_projection);
	if (fdf->settings.map_projection == PARALLEL_PROJECTION)
		ft_plane_shift(fdf, NULL);
	ft_draw_vector_points(fdf);
/* 	axi.x = -1;
	while (++axi.x < fdf->plane->height)
	{
		axi.y = -1;
		while (++axi.y < fdf->plane->widht)
		{
			p1 = fdf->plane->basis[axi.x][axi.y].axi;
			if ((axi.x + 1) < fdf->plane->height)
			{
				p2 = fdf->plane->basis[axi.x + 1][axi.y].axi;
				//ft_printf("A; p1.x = %i - p1.y = %i | p2.x = %i - p2.y = %i\n", p1.x, p1.y, p2.x, p2.y);
				//ft_draw_line(fdf, p1, p2);
			}
 			if ((axi.y + 1) < fdf->plane->widht)
			{
				p2 = fdf->plane->basis[axi.x][axi.y + 1].axi;
				//ft_printf("B; p1.x = %i - p1.y = %i | p2.x = %i - p2.y = %i\n\n", p1.x, p1.y, p2.x, p2.y);
				//ft_draw_line(fdf, p1, p2);
			}
			break;
		}
		break;
	} */
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
	mlx_key_hook(fdf->window, &ft_keyhook_camera, fdf);
	mlx_scroll_hook(fdf->window, &ft_scrollhook_zoom, fdf);
	mlx_loop(fdf->window);
}
