/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation_hooks_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:28:55 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 16:18:46 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_rotate_x_axi(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (env->settings.rotation_direction > 0)
		env->settings.rotation_axi.x++;
	if (env->settings.rotation_direction < 0)
		env->settings.rotation_axi.x--;
}

void	ft_rotate_y_axi(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (env->settings.rotation_direction > 0)
		env->settings.rotation_axi.y++;
	if (env->settings.rotation_direction < 0)
		env->settings.rotation_axi.y--;
}

void	ft_rotate_z_axi(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	if (env->settings.rotation_direction > 0)
		env->settings.rotation_axi.z++;
	if (env->settings.rotation_direction < 0)
		env->settings.rotation_axi.z--;
}
