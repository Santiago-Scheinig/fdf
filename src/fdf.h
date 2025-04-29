/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:21 by sscheini          #+#    #+#             */
/*   Updated: 2025/04/29 20:04:19 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIN_WIDHT 1980
# define WIN_HEIGHT 1080
# define M_PI 3.14159265358979323846
# define AXI_X 1
# define AXI_Y 2
# define AXI_Z 3
# define PARALLEL_PROJECTION 0
# define ISOMETRIC_PROJECTION 1

/*--------------------------------------------------------------------------*/
/*---------------------------------TYPE_DEF---------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_axi_xyz
{
	int	x;
	int	y;
	int	z;
}	t_axi_xyz;

typedef struct s_vector
{
	t_axi_xyz	axi;
	int			colour;
}	t_vector;

typedef struct s_map
{
	t_vector	**basis;
	t_vector	**shift;//edit to erase
	int			height;
	int			widht;
	int			depth;
}	t_map;

typedef struct s_program
{
	int				map_projection;
	t_axi_xyz		map_center;
	t_axi_xyz		map_zoom;
	t_axi_xyz		rotation_axi;
	int				rotation_degrees;
	int				axi_value;
	int				speed_value;
	float			zoom_value;
}	t_program;

typedef struct s_fdf
{
	t_map			plane;
	mlx_t			*window;
	mlx_image_t		*img;
	t_program		settings;
}	t_fdf;

typedef t_axi_xyz (*t_projection)(t_axi_xyz px);

/*--------------------------------------------------------------------------*/
/*----------------------------------HOOKS-----------------------------------*/
/*--------------------------------------------------------------------------*/

void	ft_keyhook_camera(mlx_key_data_t keydata, void *param);

void	ft_scrollhook_zoom(double xdelta, double ydelta, void* param);

/*--------------------------------------------------------------------------*/
/*----------------------------------CAMERA----------------------------------*/
/*--------------------------------------------------------------------------*/

t_axi_xyz	ft_rotate_x(t_axi_xyz px, double angle_degree);

t_axi_xyz	ft_rotate_y(t_axi_xyz px, double angle_degree);

t_axi_xyz	ft_rotate_z(t_axi_xyz px, int angle_degree);

t_axi_xyz	ft_isometric_projection(t_axi_xyz px);

int		ft_get_colour(char *colour);

void	ft_plane_shift(t_fdf *fdf, t_projection ft_view);

void	ft_draw_image(t_fdf *fdf);

void	ft_forcend(t_fdf *fdf, int errin);

void	ft_default_settings(t_fdf *env, int camera_pov);

void	ft_loading_animation(t_fdf *env);

#endif