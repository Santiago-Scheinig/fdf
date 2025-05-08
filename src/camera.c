/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:22 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/08 14:14:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "index.h"

/**
 * 
 * FINISHED
 * 
 */
t_axi_xyz	ft_rotate_x(t_axi_xyz px, double angle_degree)
{
	t_axi_xyz	tmp;
	double		angle_radian;

	tmp.y = px.y;
	tmp.z = px.z;
	angle_radian = angle_degree * (M_PI / 180);
	px.y = tmp.y * cos(angle_radian) - tmp.z * sin(angle_radian);
	px.z = tmp.y * sin(angle_radian) + tmp.z * cos(angle_radian);
	return (px);
}

/**
 * 
 * FINISHED
 * 
 */
t_axi_xyz	ft_rotate_y(t_axi_xyz px, double angle_degree)
{
	t_axi_xyz	tmp;
	double		angle_radian;

	tmp.x = px.x;
	tmp.z = px.z;
	angle_radian = angle_degree * (M_PI / 180);
	px.x = tmp.x * cos(angle_radian) - tmp.z * sin(angle_radian);
	px.z = -tmp.x * sin(angle_radian) + tmp.z * cos(angle_radian);
	return (px);
}

/**
 * 
 * FINISHED
 * 
 */
t_axi_xyz	ft_rotate_z(t_axi_xyz px, int angle_degree)
{
	t_axi_xyz	tmp;
	double		angle_radian;

	tmp.x = px.x;
	tmp.y = px.y;
	angle_radian = angle_degree * (M_PI / 180);
	px.x = tmp.x * cos(angle_radian) - tmp.y * sin(angle_radian);
	px.y = tmp.x * sin(angle_radian) + tmp.y * cos(angle_radian);
	return (px);
}

/**
 * 
 * FINISHED
 * 
 */
t_axi_xyz	ft_isometric_projection(t_axi_xyz px)
{
	t_axi_xyz	tmp;
	double		angle_radian;

	tmp.x = px.x;
	tmp.y = px.y;
	angle_radian = 30 * (M_PI / 180);
	px.x = (tmp.x - tmp.y) * cos(angle_radian);
	px.y = (tmp.x + tmp.y) * sin(angle_radian) - px.z;
	return (px);
}
