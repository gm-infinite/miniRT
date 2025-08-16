/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:45:44 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 14:37:21 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_ray	ray_constructor(t_vector direction, t_point origin)
{
	t_ray	ret;

	ret.direction = direction;
	ret.origin = origin;
	ret.t = -1;
	return (ret);
}

t_plane	plane(t_vector direction, t_point origin)
{
	t_plane	ret;

	ret.direction = direction;
	ret.origin = origin;
	return (ret);
}

t_sphere	sphere(t_point origin, double radius)
{
	t_sphere	ret;

	ret.origin = origin;
	ret.radius = radius;
	ret.relative_cam_pos = vector(0, 0, 0);
	return (ret);
}

t_cylinder	cylinder(t_vector direction, t_point origin,
					double radius, double height)
{
	t_cylinder	ret;

	ret.direction = direction;
	ret.origin = origin;
	ret.radius = radius;
	ret.h = height;
	ret.relative_cam_pos = vector(0, 0, 0);
	return (ret);
}

void	set_sphere_relative_cam_pos(t_sphere *sphere, t_point cam_pos)
{
	sphere->relative_cam_pos = point_substract(cam_pos, sphere->origin);
}

void	set_cylinder_relative_cam_pos(t_cylinder *cylinder, t_point cam_pos)
{
	t_vector	cam_relative_to_origin;

	cam_relative_to_origin = point_substract(cam_pos, cylinder->origin);
	cylinder->relative_cam_pos = vector_transform(cam_relative_to_origin, cylinder);
}
