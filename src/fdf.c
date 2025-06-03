/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 17:43:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * A hook to the escape key, which will close the program after freeing all
 * allocated memory.
 * @param keydata The data of the key being pressed.
 * @param param A VOID * to the parameter to be used if the hook triggers,
 * the main fdf structure in this case.
 */
static void	ft_keyhook_exit(mlx_key_data_t keydata, void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_forcend(env, MLX_SUCCESS);
}

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
 * Fdf is a program capable of printing an .fdf map file as a
 * three dimensional image on it's own program window.
 */
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	env;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf\0", ft_strlen(argv[1])))
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
	mlx_key_hook(env.window, ft_keyhook_exit, &env);
	mlx_loop(env.window);
	ft_forcend(&env, MLX_SUCCESS);
}
