/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/23 16:24:06 by kuzyilma         ###   ########.fr       */
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

double cylinder_intersection(t_ray ray, t_cylinder cy)
{
    t_ray ray_m;
    double t;
    double t_plane;
    
    ray_m = ray_transform_cy(ray, &cy);
    t = -1;
    
    // Calculate infinite cylinder intersection
    double a = (ray_m.direction.x * ray_m.direction.x) + (ray_m.direction.z * ray_m.direction.z);
    
    // Skip calculation if ray is parallel to cylinder axis
    if (a > T_ZERO_THRESHOLD)
    {
        double b = 2 * (ray_m.origin.x * ray_m.direction.x + ray_m.origin.z * ray_m.direction.z);
        double discriminant = b * b - 4 * a * ((ray_m.origin.x * ray_m.origin.x) + 
                                              (ray_m.origin.z * ray_m.origin.z) - 
                                              cy.radius * cy.radius);
        
        if (discriminant >= 0)
        {
            double t1 = (-b - sqrt(discriminant)) / (2 * a);
            double t2 = (-b + sqrt(discriminant)) / (2 * a);
            
            if (t1 > 0 && fabs(ray_m.origin.y + t1 * ray_m.direction.y) <= cy.h / 2)
                t = t1;
            else if (t2 > 0 && fabs(ray_m.origin.y + t2 * ray_m.direction.y) <= cy.h / 2)
                t = t2;
        }
    }
    
    // Check caps
    t_plane = plane_intersection(ray_m, plane(vector(0, 1, 0), vector(0, cy.h / 2, 0)));
    if (t_plane > 0)
    {
        double x = ray_m.origin.x + t_plane * ray_m.direction.x;
        double z = ray_m.origin.z + t_plane * ray_m.direction.z;
        if (x*x + z*z <= cy.radius * cy.radius && (t < 0 || t_plane < t))
            t = t_plane;
    }
    
    t_plane = plane_intersection(ray_m, plane(vector(0, -1, 0), vector(0, -cy.h / 2, 0)));
    if (t_plane > 0)
    {
        double x = ray_m.origin.x + t_plane * ray_m.direction.x;
        double z = ray_m.origin.z + t_plane * ray_m.direction.z;
        if (x*x + z*z <= cy.radius * cy.radius && (t < 0 || t_plane < t))
            t = t_plane;
    }
    
    return (t);
}
