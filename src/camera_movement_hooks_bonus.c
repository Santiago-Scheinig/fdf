/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement_hooks_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:12:47 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 17:11:41 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_move_left(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.map_center.x--;
}

void	ft_move_right(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.map_center.x++;
}

void	ft_move_up(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.map_center.y--;
}

void	ft_move_down(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.map_center.y++;
}
