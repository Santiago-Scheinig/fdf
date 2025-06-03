/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:34:39 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:47:53 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * The setting keeyhook linked to the camera keyhook.
 * @param keydata The keydata structure used to read user interaction.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is an extention of the camera keyhook loop 
 * FT_KEYHOOK_CAMERA, which reads user output to camera modifications, and 
 * saving the release on the main fdf enviroment struct to be later read by 
 * FT_REDRAW_MAP. The camera modifications include:
 * @note - Movement map change: LEFT KEY - RIGHT KEY - UP KEY - DOWN KEY. 
 * @note - Rotation map change: Q [ROTATE LEFT] - E [ROTATE RIGHT].
 */
static void	ft_keyhook_release(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		env->settings.hook_movement[0] = MLX_RELEASE;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		env->settings.hook_movement[1] = MLX_RELEASE;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		env->settings.hook_movement[2] = MLX_RELEASE;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		env->settings.hook_movement[3] = MLX_RELEASE;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_RELEASE)
		env->settings.hook_rotation[0] = MLX_RELEASE;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		env->settings.hook_rotation[1] = MLX_RELEASE;
}

/**
 * The setting keeyhook linked to the main keyhook.
 * @param keydata The keydata structure used to read user interaction.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is an extention of the main keyhook loop FT_KEYHOOK_FDF,
 * which reads user input on camera modifications, and saving the input on the
 * main fdf enviroment struct to be later read by FT_REDRAW_MAP. 
 * The camera modifications include:
 * @note - Movement map change: LEFT KEY - RIGHT KEY - UP KEY - DOWN KEY. 
 * @note - Rotation map change: Q [ROTATE LEFT] - E [ROTATE RIGHT].
 */
static void	ft_keyhook_camera(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (!env->plane.span)
		return ;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
		env->settings.hook_movement[0] = MLX_REPEAT;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
		env->settings.hook_movement[1] = MLX_REPEAT;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT)
		env->settings.hook_movement[2] = MLX_REPEAT;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT)
		env->settings.hook_movement[3] = MLX_REPEAT;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_REPEAT)
		env->settings.hook_rotation[0] = MLX_REPEAT;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_REPEAT)
		env->settings.hook_rotation[1] = MLX_REPEAT;
	ft_keyhook_release(keydata, param);
}

/**
 * The setting keeyhook linked to the main keyhook.
 * @param keydata The keydata structure used to read user interaction.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is an extention of the main keyhook loop FT_KEYHOOK_FDF,
 * which reads user input on settings modifications, and redrawing the map if
 * any relevant setting has changed. The settings read include:
 * @note - Axi rotation change: 1 [Z] - 2 [Y] - 3 [Z].
 * @note - Projection change: I [ISOMETRIC] - P [PARALLEL].
 * @note - Reset default settings: R [RESET].
 */
static void	ft_keyhook_settings(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if ((keydata.key == MLX_KEY_1 || keydata.key == MLX_KEY_KP_1)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_Z;
	if ((keydata.key == MLX_KEY_2 || keydata.key == MLX_KEY_KP_2)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_Y;
	if ((keydata.key == MLX_KEY_3 || keydata.key == MLX_KEY_KP_3)
		&& keydata.action == MLX_PRESS)
		env->settings.axi_value = AXI_X;
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		env->settings.map_projection = ISOMETRIC_PROJECTION;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		env->settings.map_projection = PARALLEL_PROJECTION;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		ft_default_settings(env, env->settings.map_projection);
	ft_draw_map(env);
}

/**
 * The zoom keeyhook linked to the program.
 * @param xdelta The scroll data on the x axi.
 * @param ydelta The scroll data on the y axi.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is addapted to work together with MLX_SCROLL_HOOK, with
 * the format of MLX_SCROLLFUNC functions 
 * [ void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param) ] to 
 * read user input. This way, user interaction with the program is read on loop, 
 * allowing input and output feedback.
 */
void	ft_scrollhook_zoom(double xdelta, double ydelta, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	(void) xdelta;
	if (ydelta > 0 && env->settings.zoom_value < 4)
		ft_zoom_in(param);
	if (ydelta < 0 && env->settings.zoom_value > 0.4)
		ft_zoom_out(param);
	ft_draw_map(env);
}

/**
 * The main keyhook linked to the program.
 * @param keydata The keydata structure used to read user interaction.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is addapted to work together with MLX_KEY_HOOK, with
 * the format of MLX_KEYHOOK functions 
 * [ void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param) ] to read user
 * input. This way, user interaction with the program is read on loop, allowing
 * input and output feedback.
 */
void	ft_keyhook_fdf(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_forcend(env, MLX_SUCCESS);
	ft_keyhook_camera(keydata, param);
	ft_keyhook_settings(keydata, param);
}
