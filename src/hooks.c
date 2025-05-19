/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:34:39 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 13:11:38 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "index.h"

/**
 * 
 *  FINISHED
 * 
 */
static void	ft_rotate(t_fdf *env, int direction)
{
	if (direction < 0)
	{
		if (env->settings.axi_value == AXI_X)
			env->settings.rotation_axi.x -= env->settings.rotation_degrees;
		if (env->settings.axi_value == AXI_Y)
			env->settings.rotation_axi.y -= env->settings.rotation_degrees;
		if (env->settings.axi_value == AXI_Z)
			env->settings.rotation_axi.z -= env->settings.rotation_degrees;
	}
	if (direction > 0)
	{
		if (env->settings.axi_value == AXI_X)
			env->settings.rotation_axi.x += env->settings.rotation_degrees;
		if (env->settings.axi_value == AXI_Y)
			env->settings.rotation_axi.y += env->settings.rotation_degrees;
		if (env->settings.axi_value == AXI_Z)
			env->settings.rotation_axi.z += env->settings.rotation_degrees;
	}
}

/**
 * 
 * WORKS - CAN I OPTIMIZE EXECUTIONS WITH MLX_LOOP_HOOK?
 * 
 */
static void	ft_camera_rotation(mlx_key_data_t keydata, t_fdf *env)
{
	if ((keydata.key == MLX_KEY_1 || keydata.key == MLX_KEY_KP_1)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_Z;
	if ((keydata.key == MLX_KEY_2 || keydata.key == MLX_KEY_KP_2)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_Y;
	if ((keydata.key == MLX_KEY_3 || keydata.key == MLX_KEY_KP_3)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_X;
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS
		&& env->settings.rotation_degrees <= 85)
		env->settings.rotation_degrees += 5;
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS
		&& env->settings.rotation_degrees >= 10)
		env->settings.rotation_degrees -= 5;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		ft_rotate(env, -1);
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		ft_rotate(env, 1);
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		env->settings.map_projection = ISOMETRIC_PROJECTION;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		env->settings.map_projection = PARALLEL_PROJECTION;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		ft_default_settings(env, env->settings.map_projection);
}

/**
 * 
 * WORKS - CAN I OPTIMIZE EXECUTIONS WITH MLX_LOOP_HOOK?
 * 
 */
void	ft_scrollhook_zoom(double xdelta, double ydelta, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	(void) xdelta;
	if (ydelta > 0 && env->settings.zoom_value < 4)
		env->settings.zoom_value += 0.1;
	if (ydelta < 0 && env->settings.zoom_value > 0.4)
		env->settings.zoom_value -= 0.1;
	if (env->settings.map_projection == ISOMETRIC_PROJECTION)
		ft_draw_map(env);
	if (env->settings.map_projection == PARALLEL_PROJECTION)
		ft_draw_map(env);
}

/**
 * 
 * WORKS - CAN I OPTIMIZE EXECUTIONS WITH MLX_LOOP_HOOK?
 * 
 * //ver como optimizar varios input a la vez
 */
void	ft_keyhook_camera(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT
		&& env->settings.map_center.x > 0)
		env->settings.map_center.x -= env->settings.speed_value;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT
		&& env->settings.map_center.x < (int) env->map->width)
		env->settings.map_center.x += env->settings.speed_value;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT
		&& env->settings.map_center.y > 0)
		env->settings.map_center.y -= env->settings.speed_value;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT
		&& env->settings.map_center.y < (int) env->map->height)
		env->settings.map_center.y += env->settings.speed_value;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_forcend(env, MLX_SUCCESS);
	else
		ft_camera_rotation(keydata, env);
	if (env->settings.map_projection == ISOMETRIC_PROJECTION)
		ft_draw_map(env);
	if (env->settings.map_projection == PARALLEL_PROJECTION)
		ft_draw_map(env);
}
