/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:21 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 15:23:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "../libft/include/libft.h"
# include "MLX42_Int.h"
# include "MLX42.h"

# define WIN_WIDHT 1980
# define WIN_HEIGHT 1080
# define M_PI 3.14159265358979323846
# define AXI_X 1
# define AXI_Y 2
# define AXI_Z 3
# define PARALLEL_PROJECTION 1
# define ISOMETRIC_PROJECTION 2

/*--------------------------------------------------------------------------*/
/*---------------------------------TYPE_DEF---------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_axi_xyz
{
	int	x;
	int	y;
	int	z;
}	t_axi_xyz;

typedef struct s_double_axi
{
	double	x;
	double	y;
	double	z;
}	t_double_axi;

typedef struct s_vector
{
	t_axi_xyz	axi;
	int			colour;
}	t_vector;

typedef struct s_map
{
	t_list		*span;
	int			depth;
	int			widht;
	int			height;
}	t_map;

typedef struct s_program
{
	t_axi_xyz		map_center;
	t_axi_xyz		rotation_axi;
	int				hook_movement[4];
	int				hook_rotation[2];
	int				axi_value;
	int				map_projection;
	int				rotation_direction;
	float			zoom_value;
}	t_program;

typedef struct s_fdf
{
	mlx_t			*window;
	mlx_image_t		*map;
	mlx_image_t		*bg;
	mlx_image_t		*bg_name;
	t_map			plane;
	t_program		settings;
}	t_fdf;

typedef t_axi_xyz	(*t_projection)(t_axi_xyz px);

/*--------------------------------------------------------------------------*/
/*-----------------------------------FDF------------------------------------*/
/*--------------------------------------------------------------------------*/

void		ft_default_settings(t_fdf *env, int camera_view);

void		ft_forcend(t_fdf *fdf, int errin);

/*--------------------------------------------------------------------------*/
/*-----------------------------------MATH-----------------------------------*/
/*--------------------------------------------------------------------------*/

t_axi_xyz	ft_rotate_x(t_axi_xyz px, double angle_degree);

t_axi_xyz	ft_rotate_y(t_axi_xyz px, double angle_degree);

t_axi_xyz	ft_rotate_z(t_axi_xyz px, int angle_degree);

t_axi_xyz	ft_isometric_projection(t_axi_xyz px);

/*--------------------------------------------------------------------------*/
/*----------------------------------DRAW------------------------------------*/
/*--------------------------------------------------------------------------*/

void		ft_dda(t_fdf *fdf, t_vector a, t_vector b, int color);

void		ft_draw_background(mlx_image_t *img, int color);

void		ft_draw_line(t_fdf *env, t_vector *line, t_vector *prev);

void		ft_draw_map(void *param);

/*--------------------------------------------------------------------------*/
/*----------------------------------START-----------------------------------*/
/*--------------------------------------------------------------------------*/

void		ft_fdf_init(t_fdf *env, int fd, char *file_name);

void		ft_map_init(t_fdf *env);

/*--------------------------------------------------------------------------*/
/*----------------------------------UTILS-----------------------------------*/
/*--------------------------------------------------------------------------*/

int			ft_get_depth(t_fdf *env);

int			ft_get_widht(t_fdf *env);

int			ft_get_colour(char *colour, int z);

int			ft_depth_color(t_vector a, t_vector b);

t_vector	ft_apply_planeshift(t_fdf *env, t_vector px);

#endif