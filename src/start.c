/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:01:09 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/08 18:33:28 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "index.h"

/**
 * Initializes each T_VECTOR on it's default T_MAP basis, giving each axi
 * it's correspondent X, Y and Z value.
 * @param[in] fdf The main setting fdf structure.
 * @param[in] plane The text based three dimensional plane values.
 * @note It also saves the pixel colour if it's detailed. If not, it sets it
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
			break;
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
 * @param[out] fdf The main fdf setting structure.
 * @param[in] file_name The name of the .fdf file or absolute path to it.
 * @note If any error occurs, the program ends.
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
 * 
 * PENDING - USER MENU - Static Linked to ft_fdf_init
 * CANT MAKE A LOADING SCREEN WITHOUT A FORK SADLY.
 */
static void	ft_usr_init(t_fdf *env, char *file_name)
{
	mlx_image_t	*title;
	mlx_image_t	*file;

	env->menu = mlx_new_image(env->window, ((2 * WIN_WIDHT) / 10), WIN_HEIGHT);
	if (!env->menu)
		ft_forcend(env, MLX_MEMFAIL);
	ft_draw_background(env->menu, 0x844900);
	mlx_image_to_window(env->window, env->menu, env->bg->width, 0);
	title = mlx_put_string(env->window, "FDF", env->bg->width + (env->menu->width / 5), 0);
	file = mlx_put_string(env->window, file_name, 20, env->bg->height - 20);
	mlx_resize_image(title, 200, 200);
}

/**
 * 
 * WORKS - MIGHT NEED IMPROVEMENT IF NEW FUNCTIONS ARE ADDED
 * 
 */
void	ft_fdf_init(t_fdf *env, int fd, char *file_name)
{
	int x;
	int	y;

	env->bg = NULL;
	env->map = NULL;
	env->menu = NULL;
	env->window = NULL;
	env->plane.span = NULL;
	env->window = mlx_init(WIN_WIDHT, WIN_HEIGHT, "FDF", true);
	if (!env->window)
		ft_forcend(env, MLX_WINFAIL);
	x = WIN_WIDHT - ((2 * WIN_WIDHT) / 10);
	y = WIN_HEIGHT;
	env->bg = mlx_new_image(env->window, x, y);
	if (!env->bg)
		ft_forcend(env, MLX_MEMFAIL);
	ft_draw_background(env->bg, 0x000000);
	mlx_image_to_window(env->window, env->bg, 0, 0);
	ft_usr_init(env, file_name);
	env->plane.height = ft_read_file(&env->plane.span, fd);
	if (env->plane.height < 0)
		ft_forcend(env, MLX_MEMFAIL);
	env->plane.widht = ft_get_widht(env);
	env->plane.depth = ft_get_depth(env);
}
