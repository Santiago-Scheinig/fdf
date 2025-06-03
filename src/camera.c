/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:26:22 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/03 17:32:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi X of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
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
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi Y of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
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
 * Perfoms the necesary matrix mathematics to calculate the rotation on the
 * axi Z of a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @param angle_degree The angle to which the T_AXI_XYZ point will be rotated.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
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
 * Perfoms the necesary matrix mathematics to calculate the isometric
 * projection a T_AXI_XYZ point.
 * @param px The origin T_AXI_XYZ point.
 * @return The resultant T_AXI_XYZ point of the matrix calculation.
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

/**
 * Performs the necesary matrix mathematics to calculate all shifts to be
 * done to a T_VECTOR point.
 * @param env The main fdf enviroment structure.
 * @param px The origin T_VECTOR point.
 * @return The resultant T_VECTOR point after all calculation are done.
 * @note By default, the rotation on all axis are 0. 
 */
t_vector	ft_apply_planeshift(t_fdf *env, t_vector px)
{
	px.axi.x *= env->settings.zoom_value;
	px.axi.y *= env->settings.zoom_value;
	px.axi.z *= env->settings.zoom_value;
	if (env->settings.rotation_axi.x)
		px.axi = ft_rotate_x(px.axi, env->settings.rotation_axi.x);
	if (env->settings.rotation_axi.y)
		px.axi = ft_rotate_y(px.axi, env->settings.rotation_axi.y);
	if (env->settings.rotation_axi.z)
		px.axi = ft_rotate_z(px.axi, env->settings.rotation_axi.z);
	if (env->settings.map_projection == ISOMETRIC_PROJECTION)
		px.axi = ft_isometric_projection(px.axi);
	px.axi.x += env->settings.map_center.x;
	px.axi.y += env->settings.map_center.y;
	return (px);
}
