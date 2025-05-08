/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/08 18:30:14 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "index.h"

/**
 * Fdf failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param[in] env The main environment fdf structure.
 * @param[in] errin The MLX index number of the error in question.
 */
void	ft_forcend(t_fdf *env, int errin)
{
	if ((*env).plane.span)
		ft_lstclear(&env->plane.span, free);
	if ((*env).menu)
		mlx_delete_image(env->window, env->menu);
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
 * 
 *	FINISHED - Optimized to be a reset button only, that way math is calculated
 * 	only when needed;
 * 
 */
void	ft_default_settings(t_fdf *env, int camera_view)
{
	env->settings.axi_value = AXI_Z;
	env->settings.map_center.x = (env->bg->width / 2);
	env->settings.map_center.y = (env->bg->height / 2);
	env->settings.rotation_axi.x = 0;
	env->settings.rotation_axi.y = 0;
	env->settings.rotation_axi.z = 0;
	env->settings.zoom_value = 0.5;
	env->settings.speed_value = 5;
	env->settings.map_projection = camera_view;
	env->settings.rotation_degrees = 45;
}

/**
 * Fdf is a program capable of printing an .fdf map file as a
 * three dimensional image on it's own program window.
 */
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	env;

	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
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
	mlx_key_hook(env.window, ft_keyhook_camera, &env);
	mlx_scroll_hook(env.window, ft_scrollhook_zoom, &env);
	mlx_loop(env.window);
	ft_forcend(&env, MLX_SUCCESS);
}
