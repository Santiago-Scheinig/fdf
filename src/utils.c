/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:52:10 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/02 18:20:18 by sscheini         ###   ########.fr       */
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
		{
			if (env->plane.basis[axi.y][axi.x].axi.z < 0)
			{
				if (axi.z < (env->plane.basis[axi.y][axi.x].axi.z * -1))
					axi.z = env->plane.basis[axi.y][axi.x].axi.z * -1;
			}
			else if (axi.z < env->plane.basis[axi.y][axi.x].axi.z)
				axi.z = env->plane.basis[axi.y][axi.x].axi.z;
		}
	}
	return (axi.z);
}

int	ft_get_colour(char *colour, int z)
{
	int			ans;
	
	if (!colour)
	{
		if (z > 0)
			return (0xFF0000 - (0x001111 * z));
		if (z < 0)
			return (0x0000FF + (0x111100 * z));
		return (0xFFFFFF);
	}
	colour += 3;
	ans = ft_atoi_base(colour, "0123456789abcdef");
	if (!ans)
		return (ft_atoi_base(colour, "0123456789ABCDEF"));
	return (ans);
}

t_vector	ft_plane_shift(t_fdf *env, t_vector px, t_projection ft_shift)
{
	px.axi.x *= (env->settings.map_zoom.x * env->settings.zoom_value);
	px.axi.y *= (env->settings.map_zoom.y * env->settings.zoom_value);
	px.axi.z *= (env->settings.map_zoom.z * env->settings.zoom_value);
	px.axi = ft_rotate_x(px.axi, env->settings.rotation_axi.x);
	px.axi = ft_rotate_y(px.axi, env->settings.rotation_axi.y);
	px.axi = ft_rotate_z(px.axi, env->settings.rotation_axi.z);
	if (ft_shift)
		px.axi = ft_shift(px.axi);
	px.axi.x += env->settings.map_center.x;
	px.axi.y += env->settings.map_center.y;
	return (px);
}

void	ft_default_settings(t_fdf *env, int camera_view)
{
	env->plane.depth = ft_get_maxdepth(env) * 2;
	if (!env->plane.depth)
		env->plane.depth = 1;
	env->settings.map_projection = camera_view;
	env->settings.map_center.x = (env->map->width / 2);
	env->settings.map_center.y = (env->map->height / 2);
	env->settings.map_zoom.x = (env->map->height / env->plane.widht);
	env->settings.map_zoom.y = (env->map->height / env->plane.height);
	env->settings.map_zoom.z = ((env->map->height / 2) / env->plane.depth);
	env->settings.rotation_axi.x = 0;
	env->settings.rotation_axi.y = 0;
	env->settings.rotation_axi.z = 0;
	env->settings.rotation_degrees = 45;
	env->settings.axi_value = AXI_Z;
	env->settings.speed_value = 5;
	env->settings.zoom_value = 0.5;
}
