/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/04 13:56:08 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

int	plane_intersection(t_ray ray, t_plane plane, t_intersection *inter)
{
	double		d;
	t_vector	normal;

	d = v3_dot(plane.direction, ray.direction);
	if (fabs(d) < T_ZERO_THRESHOLD)
		return (0);
	ray.t = v3_dot(point_substract(plane.origin, ray.origin),
			plane.direction) / d;
	if (ray.t < T_ZERO_THRESHOLD)
		return (0);
	if (inter->t < 0 || ray.t < inter->t)
	{
		if (d > 0)
			normal = v3_mult(-1, plane.direction);
		else
			normal = plane.direction;
		*inter = intersection_constructor(ray.t, normal, plane.color);
		return (1);
	}
	return (0);
}

int	sphere_intersection(t_ray ray, t_sphere sphere, t_intersection *inter)
{
	double		t2;
	t_vector	oc;
	double		b;
	double		discriminant;

	oc = point_substract(ray.origin, sphere.origin);
	b = 2.0 * v3_dot(oc, ray.direction);
	discriminant = (b * b) - (4.0 * (v3_dot(oc, oc)
				- (sphere.radius * sphere.radius)));
	if (discriminant < 0)
		return (0);
	ray.t = (-b - sqrt(discriminant)) / 2.0;
	t2 = (-b + sqrt(discriminant)) / 2.0;
	if (ray.t < T_ZERO_THRESHOLD)
	{
		if (t2 < T_ZERO_THRESHOLD)
			return (0);
		ray.t = t2;
	}
	if (inter->t >= 0 && ray.t >= inter->t)
		return (0);
	*inter = intersection_constructor(ray.t, v3_norm(point_substract(p3_add(
						ray.origin, v3_mult(ray.t, ray.direction)),
					sphere.origin)), sphere.color);
	return (1);
}

double	cylinder_side_intersection(t_ray r, t_cylinder cy)
{
	double	b;
	double	discriminant;
	double	a;
	double	tt;

	a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
	b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
	discriminant = b * b - 4 * a
		* ((r.origin.x * r.origin.x)
			+ (r.origin.z * r.origin.z) - cy.radius * cy.radius);
	r.t = -1;
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
	return (r.t);
}

int	cylinder_cap_intersection(t_ray ray_m, t_cylinder cy,
			t_plane cap_plane, double *current_t)
{
	double			t_plane;
	double			x;
	double			z;
	t_intersection	temp_inter;

	temp_inter.t = -1;
	plane_intersection(ray_m, cap_plane, &temp_inter);
	t_plane = temp_inter.t;
	if (t_plane <= 0)
		return (0);
	x = ray_m.origin.x + t_plane * ray_m.direction.x;
	z = ray_m.origin.z + t_plane * ray_m.direction.z;
	if (x * x + z * z <= cy.radius * cy.radius
		&& (*current_t < 0 || t_plane < *current_t))
	{
		*current_t = t_plane;
		return (1);
	}
	return (0);
}

t_vector	calculate_cylinder_normal(t_ray ray, t_cylinder cy, double t,
		int hit_type)
{
	t_vector	normal;
	t_point		world_hit_point;
	t_vector	to_hit;
	t_vector	projected_on_axis;
	double		projection;

	world_hit_point = p3_add(ray.origin, v3_mult(t, ray.direction));
	to_hit = point_substract(world_hit_point, cy.origin);
	if (hit_type == 0)
	{
		projected_on_axis = v3_mult(v3_dot(to_hit,
					cy.direction), cy.direction);
		normal = v3_norm(v3_sub(to_hit, projected_on_axis));
	}
	else
	{
		projection = v3_dot(to_hit, cy.direction);
		if (projection > 0)
			normal = cy.direction;
		else
			normal = v3_mult(-1, cy.direction);
	}
	return (normal);
}
