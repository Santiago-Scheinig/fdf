/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:45:20 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 18:42:44 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/**
 * Fdf failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param env The main environment fdf structure.
 * @param errin The MLX index number of the error in question.
 */
void	ft_forcend(t_fdf *env, int errin)
{
	if ((*env).plane.span)
		ft_lstclear(&env->plane.span, free);
	if ((*env).bg_name)
		mlx_delete_image(env->window, env->bg_name);
	if ((*env).map)
		mlx_delete_image(env->window, env->map);
	if ((*env).bg)
		mlx_delete_image(env->window, env->bg);
	if ((*env).window)
		mlx_terminate(env->window);
	if (errin)
	{
		ft_printfd(2, "Error: %s.\n", mlx_strerror(errin));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/**
 * Sets the default settings of the fdf program.
 * @param env The main enviroment fdf structure.
 * @param camera_view The camera view which the map will be display.
 */
void	ft_default_settings(t_fdf *env, int camera_view)
{
	env->settings.hook_movement[0] = 0;
	env->settings.hook_movement[1] = 0;
	env->settings.hook_movement[2] = 0;
	env->settings.hook_movement[3] = 0;
	env->settings.hook_rotation[0] = 0;
	env->settings.hook_rotation[1] = 0;
	env->settings.axi_value = AXI_Z;
	env->settings.map_center.x = (env->bg->width / 2);
	env->settings.map_center.y = (env->bg->height / 2);
	env->settings.rotation_axi.x = 0;
	env->settings.rotation_axi.y = 0;
	env->settings.rotation_axi.z = 0;
	env->settings.rotation_direction = 1;
	env->settings.zoom_value = 0.5;
	env->settings.map_projection = camera_view;
}

/**
 * Reads in wich AXI the user is interacting, and rotates the respected AXI
 * in accordance to user input.
 * @param env The main fdf enviroment structure.
 * @param direction The direction of the rotation: left [-x], right [+x].
 */
static void	ft_rotate(t_fdf *env, int direction)
{
	env->settings.rotation_direction = direction;
	if (env->settings.axi_value == AXI_X)
		ft_rotate_x_axi(env);
	if (env->settings.axi_value == AXI_Y)
		ft_rotate_y_axi(env);
	if (env->settings.axi_value == AXI_Z)
		ft_rotate_z_axi(env);
}

/**
 * Verifies the user input to interact with the map, and if any interaction
 * it's made, then the map is modified and reprinted in screen.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is addapted to work together with MLX_LOOP_HOOK, with
 * the format of generic functions [ void (*f)(void*) ] to be executed 
 * frame by frame on loop. This way, user interaction with the program is 
 * time reestricted to the machine proccess of each execution.
 */
static void	ft_redraw_map(void *param)
{
	t_fdf	*env;
	int		shift;

	shift = 1;
	env = (t_fdf *) param;
	if (env->settings.hook_movement[0] && env->settings.map_center.x > 0)
		ft_move_left(env);
	else if (env->settings.hook_movement[1]
		&& env->settings.map_center.x < (int) env->map->width)
		ft_move_right(env);
	else if (env->settings.hook_movement[2] && env->settings.map_center.y > 0)
		ft_move_up(env);
	else if (env->settings.hook_movement[3]
		&& env->settings.map_center.y < (int) env->map->height)
		ft_move_down(env);
	else if (env->settings.hook_rotation[0])
		ft_rotate(env, -1);
	else if (env->settings.hook_rotation[1])
		ft_rotate(env, 1);
	else
		shift = 0;
	if (shift)
		ft_draw_map(env);
	mlx_image_to_window(env->window, env->map, 0, 0);
}

/**
 * Fdf is a program capable of printing an .fdf map file as a
 * three dimensional image on it's own program window.
 */
int	main(int argc, char **argv)
{
	int			fd;
	t_fdf		env;

	if (argc != 2 || ft_memcmp(ft_strchr(argv[1], '.'), ".fdf\0", 5))
	{
		ft_printfd(STDERR_FILENO, "Error: %s.\n", mlx_strerror(MLX_INVEXT));
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printfd(STDERR_FILENO, "Error: %s.\n", mlx_strerror(MLX_INVFILE));
		exit(EXIT_FAILURE);
	}
	ft_fdf_init(&env, fd, argv[1]);
	close(fd);
	if (env.plane.height)
		ft_map_init(&env);
	mlx_key_hook(env.window, ft_keyhook_fdf, &env);
	mlx_scroll_hook(env.window, ft_scrollhook_zoom, &env);
	if (!mlx_loop_hook(env.window, ft_redraw_map, &env))
		ft_forcend(&env, MLX_WINFAIL);
	mlx_loop(env.window);
	ft_forcend(&env, MLX_SUCCESS);
}
