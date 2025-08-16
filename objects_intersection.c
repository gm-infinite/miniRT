/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 12:53:57 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

double	plane_intersection(t_ray ray, t_plane plane)
{
	double	d;
	double	t;

	d = vector_dot_product(plane.direction, ray.direction);
	if (fabs(d) < T_ZERO_THRESHOLD)
		return (-1);
	t = vector_dot_product(point_substract(plane.origin, ray.origin),
			plane.direction) / d;
	if (t < T_ZERO_THRESHOLD)
		return (-1);
	return (t);
}

double	sphere_intersection(t_ray ray, t_sphere sphere)
{
	double					t1;
	double					t2;
	t_vector				oc;
	double					b;
	double					discriminant;

	oc = point_substract(ray.origin, sphere.origin);
	b = 2.0 * vector_dot_product(oc, ray.direction);
	discriminant = (b * b) - (4.0 * (vector_dot_product(oc, oc)
				- (sphere.radius * sphere.radius)));
	if (discriminant < 0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / 2.0;
	t2 = (-b + sqrt(discriminant)) / 2.0;
	if (t1 >= T_ZERO_THRESHOLD)
		return (t1);
	else if (t2 >= T_ZERO_THRESHOLD)
		return (t2);
	return (-1);
}
