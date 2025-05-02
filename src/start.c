/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:01:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/02 18:04:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	char		*c;
	t_axi_xyz	p;

	p.y = -1;
	while (++p.y < fdf->plane.height)
	{
		fdf->plane.basis[p.y] = malloc(fdf->plane.widht * sizeof(t_vector));
		if (!fdf->plane.basis[p.y])
			ft_forcend(fdf, MLX_MEMFAIL);
		p.x = -1;
		while (++p.x < fdf->plane.widht)
		{
			if (!plane[p.y][p.x])
				break;
			fdf->plane.basis[p.y][p.x].axi.x = p.x - (fdf->plane.widht / 2);
			fdf->plane.basis[p.y][p.x].axi.y = p.y - (fdf->plane.height / 2);
			fdf->plane.basis[p.y][p.x].axi.z = ft_atoi(plane[p.y][p.x]);
			p.z = fdf->plane.basis[p.y][p.x].axi.z;
			c = ft_strnstr(plane[p.y][p.x], ",0x", ft_strlen(plane[p.y][p.x]));
			fdf->plane.basis[p.y][p.x].colour = ft_get_colour(c, p.z);
		}
		ft_split_free(plane[p.y]);
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

	fdf->plane.basis = NULL;
	fdf->plane.widht = 0;
	if (!plane || !plane[0])
		ft_forcend(fdf, MLX_INVFILE);
	fdf->plane.basis = malloc((fdf->plane.height + 1) * sizeof(t_vector *));
	//fdf->plane.shift = malloc((fdf->plane.height + 1) * sizeof(t_vector *));
	if (!fdf->plane.basis)
		ft_forcend(fdf, MLX_MEMFAIL);
	fdf->plane.basis[fdf->plane.height] = NULL;
	x = -1;
	while (plane[0][++x])
		fdf->plane.widht++;
	ft_vector_read(fdf, plane);
/* 	y = -1;
	while (fdf->plane.basis[++y])
	{
		fdf->plane.shift[y] = malloc(fdf->plane.widht * sizeof(t_vector));
		if (!fdf->plane.shift[y])
			ft_forcend(fdf, MLX_MEMFAIL);
	} */
}

/**
 * Initializes a T_MAP structure using the information included on an .fdf 
 * file.
 * @param[out] fdf The main fdf setting structure.
 * @param[in] file_name The name of the .fdf file or absolute path to it.
 * @note If any error occurs, the program ends.
 */
void	ft_map_init(t_fdf *env, char **lines)
{
	char	***plane;
	int		i;

	plane = malloc((env->plane.height + 1) * sizeof(char **));
	if (!plane)
	{
		ft_split_free(lines);
		ft_forcend(env, MLX_MEMFAIL);
	}
	plane[env->plane.height] = NULL;
	i = -1;
	while (lines[++i])
		plane[i] = ft_split(lines[i], ' ');
	ft_split_free(lines);
	ft_map_creation(env, plane);
}