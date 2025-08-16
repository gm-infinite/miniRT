/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:55:28 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 13:29:53 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "vector.h"
# define T_ZERO_THRESHOLD 0.000001

typedef t_coordinates_3d	t_point;

typedef struct s_ray
{
	t_vector	direction; //every direction needs to be normalized.  (always)
	t_point		origin;
	double		t;
}	t_ray;

typedef struct s_plane
{
	t_vector	direction; //every direction needs to be normalized.  (always)
	t_point		origin;
}	t_plane;

typedef struct s_sphere
{
	t_point		origin;
	double		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	direction; //every direction needs to be normalized.  (always)
	t_point		origin;
	double		radius;
	double		height;
	double		matrix[3][3];
}	t_cylinder;

t_ray					ray(t_vector direction, t_point origin);
t_plane					plane(t_vector direction, t_point origin);
t_sphere				sphere(t_point origin, double radius);
t_cylinder				cylinder(t_vector direction, t_point origin,
							double radius, double height);
t_ray					ray_default(void);
t_plane					plane_default(void);
t_sphere				sphere_default(void);
t_cylinder				cylinder_default(void);
t_vector				point_substract(t_point a, t_point b);

#endif
