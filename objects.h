/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:55:28 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 15:42:07 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "vector.h"
# include "color.h"
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
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_point		origin;
	double		radius;
	t_color		color;
	t_point		relative_cam_pos;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	direction; //every direction needs to be normalized.  (always)
	t_point		origin;
	double		radius;
	double		h;
	double		matrix[3][3];
	t_color		color;
	t_point		relative_cam_pos;
}	t_cylinder;

t_ray					ray_constructor(t_vector direction, t_point origin);
t_plane					plane(t_vector direction, t_point origin);
t_sphere				sphere(t_point origin, double radius);
t_cylinder				cylinder(t_vector direction, t_point origin,
							double radius, double height);
t_ray					ray_default(void);
t_plane					plane_default(void);
t_sphere				sphere_default(void);
t_cylinder				cylinder_default(void);
t_vector				point_substract(t_point a, t_point b);

void					transform_matrix(t_cylinder *cy);
t_vector				vector_transform(t_vector vector, t_cylinder *cy);
t_ray					ray_transform(t_ray ray, t_cylinder *cy);
t_point					point_add(t_point a, t_vector b);

void					set_sphere_relative_cam_pos(t_sphere *sphere, t_point cam_pos);
void					set_cylinder_relative_cam_pos(t_cylinder *cylinder, t_point cam_pos);

#endif
