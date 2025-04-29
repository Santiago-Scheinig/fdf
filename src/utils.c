/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:52:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/04/29 19:57:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_get_maxdepth(t_fdf *env)
{
	t_axi_xyz	axi;

	axi.y = -1;
	axi.z = env->plane.basis[0][0].axi.z;
	while(++axi.y < env->plane.height)
	{
		axi.x = -1;
		while(++axi.x < env->plane.widht)
			if (axi.z < env->plane.basis[axi.y][axi.x].axi.z)
				axi.z = env->plane.basis[axi.y][axi.x].axi.z;
	}
	return (axi.z);
}

int	ft_get_colour(char *colour)
{
	const char	*hex_base;
	int			ans;
	
	if (!colour)
		return (0xFFFFFF);
	colour += 3;
	hex_base = "0123456789abcdef";
	ans = ft_atoi_base(colour, hex_base);
	if (!ans)
	{
		hex_base = "0123456789ABCDEF";
		ans = ft_atoi_base(colour, hex_base);
	}
	if (!ans)
		return (0xFFFFFF);
	return (ans);
}

void	ft_plane_shift(t_fdf *env, t_projection ft_shift)
{
	t_axi_xyz	axi;
	t_axi_xyz	px;
	
	axi.y = -1;
	while (++axi.y < env->plane.height)
	{
		axi.x = -1;
		while (++axi.x < env->plane.widht)
		{
			px = env->plane.basis[axi.y][axi.x].axi;
			px.x *= (env->settings.map_zoom.x * env->settings.zoom_value);
			px.y *= (env->settings.map_zoom.y * env->settings.zoom_value);
			px.z *= (env->settings.map_zoom.z * env->settings.zoom_value);
			px = ft_rotate_x(px, env->settings.rotation_axi.x);
			px = ft_rotate_y(px, env->settings.rotation_axi.y);
			px = ft_rotate_z(px, env->settings.rotation_axi.z);
			if (ft_shift)
				px = ft_shift(px);
			env->plane.shift[axi.y][axi.x].axi = px;
		}
	}
}

void	ft_default_settings(t_fdf *env, int camera_pov)
{
	env->plane.depth = ft_get_maxdepth(env) * 2;
	if (!env->plane.depth)
		env->plane.depth = 1;
	env->settings.map_projection = camera_pov;
	env->settings.map_center.x = (env->img->width / 2);
	env->settings.map_center.y = (env->img->height / 2);
	env->settings.map_zoom.x = (env->img->height / env->plane.widht);
	env->settings.map_zoom.y = (env->img->height / env->plane.height);
	env->settings.map_zoom.z = (env->img->height / env->plane.depth);
	env->settings.rotation_axi.x = 0;
	env->settings.rotation_axi.y = 0;
	env->settings.rotation_axi.z = 0;
	env->settings.rotation_degrees = 45;
	env->settings.axi_value = AXI_Z;
	env->settings.speed_value = 5;
	env->settings.zoom_value = 0.5;
}
