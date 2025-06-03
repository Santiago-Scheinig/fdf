/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:19:22 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:37:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# include "fdf.h"

/*--------------------------------------------------------------------------*/
/*-----------------------------------HOOK-----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * The main keyhook linked to the program.
 * @param keydata The keydata structure used to read user interaction.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is addapted to work together with MLX_KEY_HOOK, with
 * the format of MLX_KEYHOOK functions 
 * [ void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param) ] to read user
 * input. This way, user interaction with the program is read on loop, allowing
 * input and output feedback.
 */
void	ft_keyhook_fdf(mlx_key_data_t keydata, void *param);

/**
 * The zoom keeyhook linked to the program.
 * @param xdelta The scroll data on the x axi.
 * @param ydelta The scroll data on the y axi.
 * @param param A VOID pointer to the main fdf enviroment structure.
 * @note This function is addapted to work together with MLX_SCROLL_HOOK, with
 * the format of MLX_SCROLLFUNC functions 
 * [ void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param) ] to 
 * read user input. This way, user interaction with the program is read on loop, 
 * allowing input and output feedback.
 */
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