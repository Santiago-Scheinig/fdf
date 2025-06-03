/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:21 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:40:45 by sscheini         ###   ########.fr       */
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

/**
 * Represents a three dimensional AXI, utilizing an INT for each x, y, z axi
 * value.
 */
typedef struct s_axi_xyz
{
	int	x;
	int	y;
	int	z;
}	t_axi_xyz;

/**
 * Represents a three dimensional AXI, utilizing a DOUBLE for each x, y, z axi
 * value.
 */
typedef struct s_double_axi
{
	double	x;
	double	y;
	double	z;
}	t_double_axi;

/**
 * Represents a vector, combining a T_AXI_XYZ structire and an INT to save the
 * colour of the respective vector.
 */
typedef struct s_vector
{
	t_axi_xyz	axi;
	int			colour;
}	t_vector;

/**
 * Represents the map, utilizing a T_LIST to save each vector of the respective
 * map on a node.
 * @note Additionaly saves the depth, withd and height of the map as an INT.
 */
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

/**
 * Sets the default settings of the fdf program.
 * @param env The main enviroment fdf structure.
 * @param camera_view The camera view which the map will be display.
 */
void		ft_default_settings(t_fdf *env, int camera_view);

/**
 * Fdf failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param env The main environment fdf structure.
 * @param errin The MLX index number of the error in question.
 */
void		ft_forcend(t_fdf *fdf, int errin);

/*--------------------------------------------------------------------------*/
/*-----------------------------------MATH-----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi X of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
 */
t_axi_xyz	ft_rotate_x(t_axi_xyz px, double angle_degree);

/**
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi Y of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
 */
t_axi_xyz	ft_rotate_y(t_axi_xyz px, double angle_degree);

/**
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi Z of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
 */
t_axi_xyz	ft_rotate_z(t_axi_xyz px, int angle_degree);

/**
 * Perfoms the necesary matrix mathematics to calculate the isometric
 * projection a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
 */
t_axi_xyz	ft_isometric_projection(t_axi_xyz px);

/**
 * Performs the necesary matrix mathematics to calculate all shifts to be
 * done to a T_VECTOR point.
 * @param env The main fdf enviroment structure.
 * @param px The origin T_VECTOR point.
 * @return The resultant T_VECTOR point after all calculation are done.
 * @note By default, the rotation on all axis are 0. 
 */
t_vector	ft_apply_planeshift(t_fdf *env, t_vector px);

/*--------------------------------------------------------------------------*/
/*----------------------------------DRAW------------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Digital Differential Analyzer (DDA) Algorithm
 * Draws a line between two T_VECTORS on the map MLX_IMAGE_T.
 * @param env The main enviroment fdf structure.
 * @param a The first vector to draw from.
 * @param b The second vector to draw to.
 * @param color The color the line will have.
 * @note All calculations are made with double to enchance pixel accuracy.
 */
void		ft_dda(t_fdf *fdf, t_vector a, t_vector b, int color);

/**
 * Draws a background on the MLX_IMAGE_T structure using the given color.
 * @param img The image to draw it's background.
 * @param color The background color.
 */
void		ft_draw_background(mlx_image_t *img, int color);

/**
 * Draws a map line defined by the current T_VECTOR and it's previous one.
 * @param env The main enviroment fdf structure.
 * @param line An array of T_VECTOR pointers that define a map line.
 * @param prev An array of T_VECTOR pointers to the previous map line,
 * if any.
 * @note The prev argument isn't obligatory, but if defined, will also
 * draw the lines needed between the both T_VECTOR pointers.
 */
void		ft_draw_line(t_fdf *env, t_vector *line, t_vector *prev);

/**
 * Draws the entire map on the MLX_IMAGE_T, displaying it on screen.
 * @param env The main enviroment fdf structure.
 * @note The function will first erase any previous pixels drawn on the 
 * MLX_IMAGE_T, allowing it to draw on an empty canvas.
 */
void		ft_draw_map(t_fdf *env);

/*--------------------------------------------------------------------------*/
/*----------------------------------START-----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Initializes the fdf program.
 * @param env The main fdf enviroment structure.
 * @param fd The file descriptor to the .fdf map.
 * @param name The file name to be printed on screen. 
 */
void		ft_fdf_init(t_fdf *env, int fd, char *file_name);

/**
 * Initializes a T_MAP structure using the information included on an .fdf 
 * file.
 * @param env The main fdf enviroment structure.
 * @note Initializing the map will also draw it on screen with an ISOMETRIC
 * PROJECTION by default.
 */
void		ft_map_init(t_fdf *env);

/*--------------------------------------------------------------------------*/
/*----------------------------------UTILS-----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Calculates the depth of the .fdf map file.
 * @param env The main fdf enviroment structure.
 */
int			ft_get_depth(t_fdf *env);

/**
 * Calculates the widht of the .fdf map file.
 * @param env The main fdf enviroment structure.
 */
int			ft_get_widht(t_fdf *env);

/**
 * Searches for the color defined on a point of the .fdf map file.
 * @param colour The STRING from where to reach the colour.
 * @param z The depth of the point which color is being saved.
 * @return The colour found.
 * @note If no color is define on the .fdf map file, a colour is assigned
 * which depends of the height passed as argument.
 */
int			ft_get_colour(char *colour, int z);

/**
 * Searches for the higher depth between two T_VECTOR points.
 * @param a The first T_VECTOR point.
 * @param b The second T_VECTOR point.
 * @return The color of the highest T_VECTOR point.
 */
int			ft_depth_color(t_vector a, t_vector b);

#endif