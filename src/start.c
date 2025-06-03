/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:01:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 17:46:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Initializes each T_VECTOR on it's default T_MAP basis, giving each axi
 * it's correspondent X, Y and Z value.
 * @param env The main enviroment fdf structure.
 * @param plane The text based three dimensional plane values.
 * @note It also saves the pixel colour detailed, if not, it sets it
 * to white.
 */
static t_vector	*ft_vector_read(t_fdf *env, char **vectors)
{
	t_vector	*column;
	char		*colour;
	static int	y;
	int			x;

	column = malloc(env->plane.widht * sizeof(t_vector));
	if (!column)
		return (NULL);
	x = -1;
	while (++x < env->plane.widht)
	{
		if (!vectors[x])
			break ;
		column[x].axi.x = x - (env->plane.widht / 2);
		column[x].axi.x *= (env->map->height / env->plane.widht);
		column[x].axi.y = y - (env->plane.height / 2);
		column[x].axi.y *= (env->map->height / env->plane.height);
		column[x].axi.z = ft_atoi(vectors[x]);
		colour = ft_strnstr(vectors[x], ",0x", ft_strlen(vectors[x]));
		column[x].colour = ft_get_colour(colour, column[x].axi.z);
		if (env->plane.depth)
			column[x].axi.z *= ((env->map->height / 4) / env->plane.depth);
	}
	y++;
	return (column);
}

/**
 * Initializes a T_MAP structure using the information included on an .fdf 
 * file.
 * @param env The main fdf enviroment structure.
 * @note Initializing the map will also draw it on screen with an ISOMETRIC
 * PROJECTION by default.
 */
void	ft_map_init(t_fdf *env)
{
	char		**vectors;
	t_list		*span;
	t_vector	*prev;
	int			i;

	i = -1;
	env->map = mlx_new_image(env->window, env->bg->width, env->bg->height);
	if (!env->map)
		ft_forcend(env, MLX_MEMFAIL);
	ft_default_settings(env, ISOMETRIC_PROJECTION);
	ft_memset(env->map->pixels, 0, env->map->height * env->map->width * BPP);
	mlx_image_to_window(env->window, env->map, 0, 0);
	span = env->plane.span;
	prev = NULL;
	while (span)
	{
		vectors = span->content;
		span->content = ft_vector_read(env, vectors);
		ft_split_free(vectors);
		if (!span->content)
			ft_forcend(env, MLX_MEMFAIL);
		ft_draw_line(env, span->content, prev);
		prev = span->content;
		span = span->next;
	}
}

/**
 * Initializes the fdf program.
 * @param env The main fdf enviroment structure.
 * @param fd The file descriptor to the .fdf map.
 * @param name The file name to be printed on screen. 
 */
void	ft_fdf_init(t_fdf *env, int fd, char *name)
{
	int	x;
	int	y;

	env->bg = NULL;
	env->map = NULL;
	env->bg_name = NULL;
	env->window = NULL;
	env->plane.span = NULL;
	env->window = mlx_init(WIN_WIDHT, WIN_HEIGHT, "FDF", false);
	if (!env->window)
		ft_forcend(env, MLX_WINFAIL);
	x = WIN_WIDHT;
	y = WIN_HEIGHT;
	env->bg = mlx_new_image(env->window, x, y);
	if (!env->bg)
		ft_forcend(env, MLX_MEMFAIL);
	ft_draw_background(env->bg, 0x000000);
	mlx_image_to_window(env->window, env->bg, 0, 0);
	env->bg_name = mlx_put_string(env->window, name, 20, env->bg->height - 20);
	env->plane.height = ft_read_file(&env->plane.span, fd);
	if (env->plane.height < 0)
		ft_forcend(env, MLX_MEMFAIL);
	env->plane.widht = ft_get_widht(env);
	env->plane.depth = ft_get_depth(env);
}
