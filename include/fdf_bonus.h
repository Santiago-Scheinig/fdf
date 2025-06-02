/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:19:22 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 15:39:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include "fdf.h"

/*--------------------------------------------------------------------------*/
/*-----------------------------------HOOK-----------------------------------*/
/*--------------------------------------------------------------------------*/

void	ft_keyhook_fdf(mlx_key_data_t keydata, void *param);

void	ft_scrollhook_zoom(double xdelta, double ydelta, void *param);

/*--------------------------------------------------------------------------*/
/*---------------------------------FT_HOOKS---------------------------------*/
/*--------------------------------------------------------------------------*/

void	ft_move_up(void *param);

void	ft_move_down(void *param);

void	ft_move_left(void *param);

void	ft_move_right(void *param);

void	ft_zoom_in(void *param);

void	ft_zoom_out(void *param);

void	ft_rotate_x_axi(void *param);

void	ft_rotate_y_axi(void *param);

void	ft_rotate_z_axi(void *param);

#endif