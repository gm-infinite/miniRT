/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:45:44 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/09/07 16:22:04 by kuzyilma         ###   ########.fr       */
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

t_intersection	intersection_constructor(double t, t_vector sf_normal,
					t_object *object, int type)
{
	t_intersection	ret;

	ret.t = t;
	ret.sf_normal = sf_normal;
	ret.object = object;
	ret.type = type;
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
	return (ret);
}

t_cylinder	cylinder(t_vector direction, t_point origin,
					double radius, double h)
{
	t_cylinder	ret;

	ret.direction = direction;
	ret.origin = origin;
	ret.radius = radius;
	ret.h = h;
	return (ret);
}
