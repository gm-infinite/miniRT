/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 13:32:18 by kuzyilma         ###   ########.fr       */
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
	double		t1;
	double		t2;
	t_vector	oc;
	double		b;
	double		discriminant;

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

double	cylinder_side_intersection(t_ray r, t_cylinder cy)
{
	double	b;
	double	discriminant;
	double	a;
	double	t;
	double	tt;

	a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
	b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
	discriminant = b * b - 4 * a
		* ((r.origin.x * r.origin.x)
			+ (r.origin.z * r.origin.z) - cy.radius * cy.radius);
	t = -1;
	if (a > T_ZERO_THRESHOLD)
	{
		if (discriminant >= 0)
		{
			tt = (-b - sqrt(discriminant)) / (2 * a);
			if (tt > 0 && fabs(r.origin.y + tt * r.direction.y) <= cy.h / 2)
				return (tt);
			tt = (-b + sqrt(discriminant)) / (2 * a);
			if (tt > 0 && fabs(r.origin.y + tt * r.direction.y) <= cy.h / 2)
				return (tt);
		}
	}
	return (t);
}

double	cylinder_intersection(t_ray ray, t_cylinder cy)
{
	t_ray	ray_m;
	double	t;
	double	t_plane;
	double	x;
	double	z;

	ray_m = ray_transform_cy(ray, &cy);
	t = cylinder_side_intersection(ray_m, cy);
	t_plane = plane_intersection(ray_m, plane(vector(0, 1, 0),
				vector(0, cy.h / 2, 0)));
	x = ray_m.origin.x + t_plane * ray_m.direction.x;
	z = ray_m.origin.z + t_plane * ray_m.direction.z;
	if (t_plane < 0 && x * x + z * z <= cy.radius * cy.radius
		&& (t < 0 || t_plane < t))
		t = t_plane;
	t_plane = plane_intersection(ray_m, plane(vector(0, -1, 0),
				vector(0, -cy.h / 2, 0)));
	x = ray_m.origin.x + t_plane * ray_m.direction.x;
	z = ray_m.origin.z + t_plane * ray_m.direction.z;
	if (t_plane < 0 && x * x + z * z <= cy.radius * cy.radius
		&& (t < 0 || t_plane < t))
		t = t_plane;
	return (t);
}
