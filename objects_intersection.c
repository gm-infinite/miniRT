/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:47:23 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

t_intersection_point	plane_intersection(t_ray ray, t_plane plane)
{
	t_intersection_point	ret;
	double					d;
	double					t;

	d = vector_dot_product(plane.direction, ray.direction);
	if (fabs(d) < T_ZERO_THRESHOLD)
		return (intersection_point_default());
	t = vector_dot_product(point_substract(plane.origin, ray.origin),
			plane.direction) / d;
	if (t < 0)
		return (intersection_point_default());
	ret.intersection_point = vector_add(ray.origin,
			vector_constant_multipy(t, ray.direction));
	ret.surface_normal = plane.direction;
	return (ret);
}

t_intersection_point	sphere_intersection(t_ray ray, t_sphere sphere)
{
	t_intersection_point	ret;
	t_vector				oc;
	double					a;
	double					b;
	double					discriminant;

	oc = point_substract(ray.origin, sphere.origin);
	a = vector_dot_product(ray.direction, ray.direction);
	b = 2.0 * vector_dot_product(oc, ray.direction);
	discriminant = (b * b) - (4.0 * a * (vector_dot_product(oc, oc)
				- (sphere.radius * sphere.radius)));
	if (discriminant < 0)
		return (intersection_point_default());
	ray.t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (ray.t < 0)
		return (intersection_point_default());
	ret.intersection_point = vector_add(ray.origin,
			vector_constant_multipy(ray.t, ray.direction));
	ret.surface_normal = vector_normilize(point_substract(
				ret.intersection_point, sphere.origin));
	return (ret);
}
