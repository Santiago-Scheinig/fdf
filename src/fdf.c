/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/27 21:05:40 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Fdf failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param[in] fdf The main setting fdf structure.
 * @param[in] errin The MLX index number of the error in question.
 */
static void	ft_forcend(t_fdf_settings *fdf, int errin)
{
	int			i;

	if (fdf->window)
		mlx_terminate(fdf->window);
	if ((*fdf->plane).height)
	{
		i = -1;
		while (fdf->plane->height[++i])
			free(fdf->plane->height[i]);
		free(fdf->plane->height);
	}
	ft_printfd(2, "Error: %s.\n", mlx_strerror(errin));
	exit(EXIT_FAILURE);
}

/**
 * Creates the T_MAP structure inside of fdf, including the map values and
 * colours, if any.
 * @param[out] fdf The main fdf setting structure.
 * @param[in] plane A 3D array which includes the z axi in acordance to an 
 * X - Y coordinates. (plane[X][Y] = "Z")
 * @note If any error occurs, the program ends.
 */
static void	ft_create_map(t_fdf_settings *fdf, char ***plane)
{
	int		x;
	int		y;

	fdf->plane->widht = 0;
	fdf->plane->height = NULL;
	if (!plane || !plane[0])
		ft_forcend(fdf, MLX_INVEXT);
	fdf->plane->height = malloc(fdf->plane->lenght * sizeof(t_axi *));
	if (!fdf->plane->height || !plane[0])
		ft_forcend(fdf, MLX_MEMFAIL);
	y = -1;
	while (plane[0][++y])
		fdf->plane->widht++;
	x = -1;
	while (plane[++x])
	{
		fdf->plane->height[x] = malloc(fdf->plane->widht * sizeof(t_axi));
		if (!fdf->plane->height[x])
			ft_forcend(fdf, MLX_MEMFAIL);
		y = -1;
		while (plane[x][++y])
			fdf->plane->height[x][y].value = ft_atoi(plane[x][y]);//atof
		ft_split_free(plane[x]);
	}
	free(plane);
}

/**
 * Initializes a T_MAP structure using the information included on an .fdf 
 * file.
 * @param[out] fdf The main fdf setting structure.
 * @param[in] file_name The name of the .fdf file or absolute path to it.
 * @note If any error occurs, the program ends.
 */
static void	ft_initialize_map(t_fdf_settings *fdf, char *file_name)
{
	char	***plane;
	char	**lines;
	int		fd;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_forcend(fdf, MLX_INVFILE);
	fdf->plane = malloc(sizeof(t_map));
	fdf->plane->lenght = ft_read_file(&lines, fd);
	close(fd);
	if (!lines)
		ft_forcend(fdf, MLX_MEMFAIL);
	plane = malloc((fdf->plane->lenght + 1) * sizeof(char **));
	if (!plane)
	{
		ft_split_free(lines);
		ft_forcend(fdf, MLX_MEMFAIL);
	}
	plane[fdf->plane->lenght] = NULL;
	i = -1;
	while (lines[++i])
		plane[i] = ft_split(lines[i], ' ');
	ft_split_free(lines);
	ft_create_map(fdf, plane);
}

/**
 * Initializes and loops a T_MLX structure, making the program window
 * in the process.
 * @param[out] fdf The main fdf setting structure.
 */
static void	ft_initialize_window(t_fdf_settings *fdf)
{
	fdf->window = NULL;
	fdf->window = mlx_init(1980, 1080, "FDF", false);
	if (!fdf->window)
		ft_forcend(fdf, MLX_WINFAIL);
	mlx_key_hook(fdf->window, &ft_keyhook, fdf->window);
	fdf->img = mlx_new_image(fdf->window, 1980, 1080);
	if (!fdf->img)
		ft_forcend(fdf, MLX_MEMFAIL);
	mlx_loop(fdf->window);
}

/**
 * Fdf is a program capable of printing an .fdf map file as a
 * three dimensions image on it's own program window.
 */
int	main(int argc, char **argv)
{
	t_fdf_settings	fdf;

	if (!argv[0])
		exit(EXIT_FAILURE);
	if (argc != 2)
	{
		ft_printfd(2, "Error: %s.\n", mlx_strerror(MLX_INVFILE));
		exit(EXIT_FAILURE);
	}
	fdf.img = NULL;
	fdf.plane = NULL;
	fdf.window = NULL;
	ft_initialize_window(&fdf);
	ft_initialize_map(&fdf, argv[1]);
	
	int x = -1;
	
	while (++x < fdf.plane->lenght)
	{
		int y = -1;
		while (++y < fdf.plane->widht)
			ft_printf("% 03i ", fdf.plane->height[x][y]);
		ft_printf("\n");
	}
	//ft_draw_map(&fdf);
	mlx_terminate(fdf.window);
	exit(EXIT_SUCCESS);
}
