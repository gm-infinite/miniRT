/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 17:39:23 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

int	plane_intersection_l(t_ray ray, t_vector l_or, t_plane plane, t_intersection *inter)
{
	double		d;
	t_vector	normal;

	d = v3_dot(plane.direction, ray.direction);
	if (fabs(d) < T_ZERO_THRESHOLD)
		return (0);
	ray.t = v3_dot(plane.origin, plane.direction) / d;
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

int	sphere_intersection_l(t_ray ray, t_vector l_or, t_sphere sphere, t_intersection *inter)
{
	t_vector	oc;
	t_vector	nor;
	double		b;
	double		di;
	int			in;

	in = 0;
	oc = v3_neg(sphere.origin);
	b = 2.0 * v3_dot(oc, ray.direction);
	di = (b * b) - (4.0 * (v3_dot(oc, oc) - (sphere.radius * sphere.radius)));
	if (di < 0)
		return (0);
	ray.t = (-b - sqrt(di)) / 2.0;
	if (ray.t < T_ZERO_THRESHOLD)
	{
		ray.t = (-b + sqrt(di)) / 2.0;
		in = -1;
	}
	if (ray.t < T_ZERO_THRESHOLD || (inter->t >= 0 && ray.t >= inter->t))
		return (0);
	nor = v3_mult(in, v3_norm(point_substract(v3_mult(ray.t, ray.direction),
			sphere.origin)));
	*inter = intersection_constructor(ray.t, nor, sphere.color);
	return (1);
}

double	cylinder_side_intersection_l(t_ray r, t_cylinder cy)
{
	double	b;
	double	discriminant;
	double	a;
	double	tt;

	a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
	b = 2 * (cy.ray_or.x * r.direction.x + cy.ray_or.z * r.direction.z);
	discriminant = b * b - 4 * a
		* ((cy.ray_or.x * cy.ray_or.x)
			+ (cy.ray_or.z * cy.ray_or.z) - cy.radius * cy.radius);
	r.t = -1;
	if (a > T_ZERO_THRESHOLD && discriminant >= 0)
	{
		tt = (-b - sqrt(discriminant)) / (2 * a);
		if (tt > T_ZERO_THRESHOLD
			&& fabs(cy.ray_or.y + tt * r.direction.y) <= cy.h / 2)
			return (tt);
		tt = (-b + sqrt(discriminant)) / (2 * a);
		if (tt > T_ZERO_THRESHOLD
			&& fabs(cy.ray_or.y + tt * r.direction.y) <= cy.h / 2)
			return (tt);
	}
	return (r.t);
}

int	cylinder_cap_intersection_l(t_ray ray_m, t_cylinder cy,
			t_plane cap_plane, double *current_t)
{
	double			t_plane;
	double			x;
	double			z;
	t_intersection	temp_inter;

	temp_inter.t = -1;
	plane_intersection_l(ray_m, cap_plane, &temp_inter);
	t_plane = temp_inter.t;
	if (t_plane <= T_ZERO_THRESHOLD)
		return (0);
	x = cy.ray_or.x + t_plane * ray_m.direction.x;
	z = cy.ray_or.z + t_plane * ray_m.direction.z;
	if (x * x + z * z <= cy.radius * cy.radius
		&& (*current_t < 0 || t_plane < *current_t))
	{
		*current_t = t_plane;
		return (1);
	}
	return (0);
}

t_vector	calculate_cylinder_normal_l(t_ray ray, t_cylinder cy, double t,
		int hit_type)
{
	t_vector	normal;
	t_point		world_hit_point;
	t_vector	to_hit;
	t_vector	projected_on_axis;
	double		projection;

	world_hit_point = p3_add(cy.ray_or, v3_mult(t, ray.direction));
	to_hit = point_substract(world_hit_point, cy.origin);
	projection = v3_dot(to_hit, cy.direction);
	projected_on_axis = v3_mult(v3_dot(to_hit, cy.direction), cy.direction);
	if (hit_type == 0)
	{
		normal = v3_norm(v3_sub(to_hit, projected_on_axis));
		if (v3_dot(normal, ray.direction) > 0)
			normal = v3_mult(-1, normal);
	}
	else
	{
		normal = v3_add(v3_mult((projection > 0),
					cy.direction), v3_mult((projection <= 0),
					v3_neg(cy.direction)));
		if (v3_dot(normal, ray.direction) > 0)
			normal = v3_mult(-1, normal);
	}
	return (normal);
}
