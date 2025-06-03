/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_zoom_hooks_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:25:49 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/02 16:31:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_zoom_in(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.zoom_value += 0.1;
}

void	ft_zoom_out(void *param)
{
	t_fdf	*env;

	env = (t_fdf *) param;
	env->settings.zoom_value -= 0.1;
}
