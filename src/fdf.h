/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:08:21 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/27 19:18:31 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_axi
{
	int	value;
	int	colour;
}	t_axi;

typedef struct s_map
{
	t_axi		**height;
	int			lenght;
	int			widht;
}	t_map;

typedef struct s_fdf_settings
{
	t_map		*plane;
	mlx_t		*window;
	mlx_image_t	*img;
}	t_fdf_settings;

void	ft_keyhook(mlx_key_data_t keydata, void *param);

#endif