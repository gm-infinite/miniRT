/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:55:28 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:16:46 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "vector.h"

typedef t_coordinates_3d	t_point;

typedef struct s_ray
{
	t_vector	direction;
	t_point		origin;
	double		t;
}	t_ray;

typedef struct s_plane
{
	t_vector	direction;
	t_point		origin;
}	t_plane;

typedef struct s_sphere
{
	t_point		origin;
	double		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	normal;
	t_point		origin;
	double		radius;
	double		height;
}	t_cylinder;

typedef struct s_intersection_point
{
	t_vector	surface_normal;
	t_point		intersection_point;
}	t_intersection_point;

t_intersection_point	intersection_point(t_vector surface_normal,
						t_point intersection_point);
t_ray					ray(t_vector direction, t_point origin);
t_plane					plane(t_vector direction, t_point origin);
t_sphere				sphere(t_point origin, double radius);
t_cylinder				cylinder(t_vector normal, t_point origin,
						double radius, double height);
t_ray					ray_default(void);
t_plane					plane_default(void);
t_sphere				sphere_default(void);
t_cylinder				cylinder_default(void);
t_intersection_point	intersection_point_default(void);
#endif
