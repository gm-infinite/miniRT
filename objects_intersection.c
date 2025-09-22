/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/09/07 17:02:51 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

int	plane_intersection(t_ray ray, t_plane plane, t_intersection *inter)
{
	double		d;
	t_vector	normal;

	d = vector_dot_product(plane.direction, ray.direction);
	if (fabs(d) < T_ZERO_THRESHOLD)
		return (0);
	ray.t = vector_dot_product(point_substract(plane.origin, ray.origin),
			plane.direction) / d;
	if (ray.t < T_ZERO_THRESHOLD)
		return (0);
	if (inter->t < 0 || ray.t < inter->t)
	{
		if (d > 0)
			normal = vector_multiply(-1, plane.direction);
		else
			normal = plane.direction;
		*inter = intersection_constructor(ray.t, normal, 0, PLANE);
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
	b = 2.0 * vector_dot_product(oc, ray.direction);
	discriminant = (b * b) - (4.0 * (vector_dot_product(oc, oc)
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
	*inter = intersection_constructor(ray.t, vector_normalize(
				point_substract(point_add(ray.origin, vector_multiply(
							ray.t, ray.direction)), sphere.origin)), 0, SPHERE);
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
	temp_inter.type = -1;
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

int	cylinder_intersection(t_ray ray, t_cylinder cy, t_intersection *inter)
{
	t_ray	ray_m;
	double	side_t, top_cap_t, bottom_cap_t, final_t;
	int hit_type = 0; // 0 = side, 1 = top cap, 2 = bottom cap

	ray_m = ray_transform_cy(ray, &cy);
	
	// Check side intersection
	side_t = cylinder_side_intersection(ray_m, cy);
	
	// Check cap intersections separately
	top_cap_t = -1;
	bottom_cap_t = -1;
	
	cylinder_cap_intersection(ray_m, cy,
		plane(vector(0, 1, 0), vector(0, cy.h / 2, 0)), &top_cap_t);
	cylinder_cap_intersection(ray_m, cy,
		plane(vector(0, -1, 0), vector(0, -cy.h / 2, 0)), &bottom_cap_t);
	
	// Find the closest valid intersection
	final_t = -1;
	
	if (side_t > 0)
	{
		final_t = side_t;
		hit_type = 0; // side
	}
	
	if (top_cap_t > 0 && (final_t < 0 || top_cap_t < final_t))
	{
		final_t = top_cap_t;
		hit_type = 1; // top cap
	}
	
	if (bottom_cap_t > 0 && (final_t < 0 || bottom_cap_t < final_t))
	{
		final_t = bottom_cap_t;
		hit_type = 2; // bottom cap
	}
	
	if (final_t > 0 && (inter->t < 0 || final_t < inter->t))
	{
		t_vector normal;
		
		if (hit_type == 0) // Side hit
		{
			// Calculate hit point in world space using original ray and t
			t_point world_hit_point = point_add(ray.origin, vector_multiply(final_t, ray.direction));
			
			// For cylinder side: normal = (hit_point - cylinder_center) projected perpendicular to cylinder axis
			t_vector to_hit = point_substract(world_hit_point, cy.origin);
			t_vector projected_on_axis = vector_multiply(vector_dot_product(to_hit, cy.direction), cy.direction);
			normal = vector_normalize(vector_substract(to_hit, projected_on_axis));
		}
		else // Cap hit (either hit_type 1 or 2)
		{
			// For caps, determine normal direction based on which end of cylinder was hit
			t_point world_hit_point = point_add(ray.origin, vector_multiply(final_t, ray.direction));
			t_vector to_hit = point_substract(world_hit_point, cy.origin);
			
			// Project the hit vector onto the cylinder axis to see which end we're closer to
			double projection = vector_dot_product(to_hit, cy.direction);
			
			if (projection > 0)
				normal = cy.direction;  // Hit the "positive" end along cylinder direction
			else
				normal = vector_multiply(-1, cy.direction);  // Hit the "negative" end
		}
		
		*inter = intersection_constructor(final_t, normal, 0, CYLINDER);
		return (1);
	}
	return (0);
}
