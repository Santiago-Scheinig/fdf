/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/04/29 19:57:18 by sscheini         ###   ########.fr       */
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

	if ((*fdf).img)
		mlx_delete_image(fdf->window, fdf->img);
	if ((*fdf).window)
		mlx_terminate(fdf->window);
	if (fdf->plane.basis)
	{
		i = -1;
		while (fdf->plane.basis[++i])
		{
			free(fdf->plane.basis[i]);
			free(fdf->plane.shift[i]);
		}
		free(fdf->plane.shift);
		free(fdf->plane.basis);
	}
	if (errin)
	{
		ft_printfd(2, "Error: %s.\n", mlx_strerror(errin));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/**
 * Initializes each T_VECTOR on it's default T_MAP basis, giving each axi
 * it's correspondent X, Y and Z value.
 * @param[in] fdf The main setting fdf structure.
 * @param[in] plane The text based three dimensional plane values.
 * @note It also saves the pixel colour if it's detailed. If not, it sets it
 * to white.
 */
static void	ft_vector_read(t_fdf *fdf, char ***plane)
{
	char		*colour;
	int			x;
	int			y;

	y = -1;
	while (++y < fdf->plane.height)
	{
		fdf->plane.basis[y] = malloc(fdf->plane.widht * sizeof(t_vector));
		if (!fdf->plane.basis[y])
			ft_forcend(fdf, MLX_MEMFAIL);
		x = -1;
		while (++x < fdf->plane.widht)
		{
			if (!plane[y][x])
				break;
			fdf->plane.basis[y][x].axi.x = x - (fdf->plane.widht / 2);
			fdf->plane.basis[y][x].axi.y = y - (fdf->plane.height / 2);
			fdf->plane.basis[y][x].axi.z = ft_atoi(plane[y][x]);
			colour = ft_strnstr(plane[y][x], ",0x", ft_strlen(plane[y][x]));
			fdf->plane.basis[y][x].colour = ft_get_colour(colour);
		}
		ft_split_free(plane[y]);
	}
	free(plane);
}

/**
 * Creates the T_MAP structure inside of fdf, including the map values and
 * colours, if any.
 * @param[out] fdf The main fdf setting structure.
 * @param[in] plane A 3D array which includes the z axi in acordance to an 
 * X - Y coordinates. (plane[X][Y] = "Z")
 * @note If any error occurs, the program ends.
 */
static void	ft_map_creation(t_fdf *fdf, char ***plane)
{
	int	x;
	int	y;

	fdf->plane.basis = NULL;
	fdf->plane.widht = 0;
	if (!plane || !plane[0])
		ft_forcend(fdf, MLX_INVFILE);
	fdf->plane.basis = malloc((fdf->plane.height + 1) * sizeof(t_vector *));
	fdf->plane.shift = malloc((fdf->plane.height + 1) * sizeof(t_vector *));
	if (!fdf->plane.basis || !fdf->plane.basis)
		ft_forcend(fdf, MLX_MEMFAIL);
	fdf->plane.basis[fdf->plane.height] = NULL;
	fdf->plane.basis[fdf->plane.height] = NULL;
	x = -1;
	while (plane[0][++x])
		fdf->plane.widht++;
	ft_vector_read(fdf, plane);
	y = -1;
	while (fdf->plane.basis[++y])
	{
		fdf->plane.shift[y] = malloc(fdf->plane.widht * sizeof(t_vector));
		if (!fdf->plane.shift[y])
			ft_forcend(fdf, MLX_MEMFAIL);
	}
}

/**
 * Initializes a T_MAP structure using the information included on an .fdf 
 * file.
 * @param[out] fdf The main fdf setting structure.
 * @param[in] file_name The name of the .fdf file or absolute path to it.
 * @note If any error occurs, the program ends.
 */
static void	ft_map_init(t_fdf *fdf, char *file_name)
{
	char	***plane;
	char	**lines;
	int		fd;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_forcend(fdf, MLX_INVFILE);
	fdf->plane.height = ft_read_file(&lines, fd);
	close(fd);
	if (!lines)
		ft_forcend(fdf, MLX_MEMFAIL);
	plane = malloc((fdf->plane.height + 1) * sizeof(char **));
	if (!plane)
	{
		ft_split_free(lines);
		ft_forcend(fdf, MLX_MEMFAIL);
	}
	plane[fdf->plane.height] = NULL;
	i = -1;
	while (lines[++i])
		plane[i] = ft_split(lines[i], ' ');
	ft_split_free(lines);
	ft_map_creation(fdf, plane);
}

/**
 * Fdf is a program capable of printing an .fdf map file as a
 * three dimensional image on it's own program window.
 */
int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		img_width;
	int		img_height;

	if (!argv[0])
		exit(EXIT_FAILURE);
	if (argc != 2 || !ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])))
	{
		ft_printfd(2, "Error: %s.\n", mlx_strerror(MLX_INVEXT));
		exit(EXIT_FAILURE);
	}
	fdf.img = NULL;
	fdf.window = NULL;
	ft_map_init(&fdf, argv[1]);
	fdf.window = mlx_init(WIN_WIDHT, WIN_HEIGHT, "FDF", false);
	if (!fdf.window)
		ft_forcend(&fdf, MLX_WINFAIL);
	img_width = WIN_WIDHT - ((2 * WIN_WIDHT) / 10);
	img_height = WIN_HEIGHT;
	fdf.img = mlx_new_image(fdf.window, img_width, img_height);
	if (!fdf.img)
		ft_forcend(&fdf, MLX_MEMFAIL);
	ft_default_settings(&fdf, ISOMETRIC_PROJECTION);
	ft_draw_image(&fdf);
	ft_forcend(&fdf, MLX_SUCCESS);
}
