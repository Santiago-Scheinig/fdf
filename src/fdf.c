/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/02 18:21:19 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Fdf failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param[in] fdf The main setting fdf structure.
 * @param[in] errin The MLX index number of the error in question.
 */
void	ft_forcend(t_fdf *fdf, int errin)
{
	int		i;

	if ((*fdf).window)
		mlx_terminate(fdf->window);
	if ((*fdf).map)
		mlx_delete_image(fdf->window, fdf->map);
	if ((*fdf).menu)
		mlx_delete_image(fdf->window, fdf->menu);
	if (fdf->plane.basis)
	{
		i = -1;
		while (fdf->plane.basis[++i])
			free(fdf->plane.basis[i]);
		free(fdf->plane.basis);
	}
	if (errin)
	{
		ft_printfd(2, "Error: %s.\n", mlx_strerror(errin));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/* 
static void	ft_usr_init(t_fdf *env)
{
	
}
*/

static void	ft_fdf_init(t_fdf *env)
{
	t_fpair	img;

	env->window = mlx_init(WIN_WIDHT, WIN_HEIGHT, "FDF", true);
	if (!env->window)
		ft_forcend(env, MLX_WINFAIL);
	img.x = WIN_WIDHT - ((2 * WIN_WIDHT) / 10);
	img.y = WIN_HEIGHT;
	env->map = mlx_new_image(env->window, img.x, img.y);
	if (!env->map)
		ft_forcend(env, MLX_MEMFAIL);
	ft_draw_background(env->map, 0x000000);
	mlx_image_to_window(env->window, env->map, 0, 0);
	//ft_usr_init(env);
	mlx_key_hook(env->window, ft_keyhook_start, env);
	mlx_loop(env->window);
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
		ft_printfd(2, "Error: %s.\n", mlx_strerror(MLX_INVEXT));
		exit(EXIT_FAILURE);
	}
	env.plane.basis = NULL;
	env.window = NULL;
	env.menu = NULL;
	env.map	= NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_forcend(&env, MLX_INVFILE);//test memory failure;
	env.plane.height = ft_read_file(&env.lines, fd);//improve efficiency;
	close(fd);
	if (!env.lines)
		ft_forcend(&env, MLX_MEMFAIL);
	ft_fdf_init(&env);
}
