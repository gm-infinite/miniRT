/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 15:41:12 by kuzyilma         ###   ########.fr       */
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

double	cylinder_intersection(t_ray ray, t_cylinder cy)
{
	t_ray	ray_m;
	t_point	i_point;
	double	t;
	double	t_plane;

	ray_m = ray_transform(ray, &cy);
	t = -1;
	t = sphere_intersection(ray_constructor(ray_m.direction,
				vector(ray_m.origin.x, 0, ray_m.origin.z)),
			sphere(cy.origin, cy.radius));
	if (t > 0)
	{
		i_point = point_add(ray.origin, vector_multiply(t, ray_m.direction));
		if (i_point.y < (cy.h) / 2 || i_point.y > -(cy.h) / 2)
			t = -1;
	}
	t_plane = plane_intersection(ray_m, plane(vector(0, 1, 0),
				vector(cy.origin.x, cy.origin.y + (cy.h / 2), cy.origin.z)));
	if (t_plane >= 0 && t_plane < t)
		t = t_plane;
	t_plane = plane_intersection(ray_m, plane(vector(0, -1, 0),
				vector(cy.origin.x, cy.origin.y - (cy.h / 2), cy.origin.z)));
	if (t_plane >= 0 && t_plane < t)
		t = t_plane;
	return (t);
}
