/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:55:28 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 12:12:33 by emgenc           ###   ########.fr       */
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
	t_vector	direction;
	double		t;
}	t_ray;

typedef struct s_ray_light
{
	t_vector	direction;
	t_point		origin;
	double		t;
}	t_ray_light;

typedef struct s_plane
{
	t_vector	direction;
	t_point		origin;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_point		origin;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	direction;
	t_point		origin;
	double		radius;
	double		h;
	double		matrix[3][3];
	t_color		color;
	t_point		ray_t_pos;
}	t_cylinder;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef union u_object_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_data;

typedef struct s_object
{
	t_object_type	type;
	t_object_data	object;
}	t_object;

typedef struct s_intersection
{
	double		t;
	t_vector	sf_normal;
	t_color		color;
}	t_intersection;

t_ray			ray_constructor(t_vector direction);
t_ray_light		ray_light_constructor(t_vector direction, t_point origin);
t_intersection	intersection_constructor(double t, t_vector sf_normal,
					t_color color);
t_plane			plane(t_vector direction, t_point origin);
t_sphere		sphere(t_point origin, double radius);
t_cylinder		cylinder(t_vector direction, t_point origin,
					double radius, double height);
t_ray			ray_default(void);
t_plane			plane_default(void);
t_sphere		sphere_default(void);
t_cylinder		cylinder_default(void);
t_vector		point_substract(t_point a, t_point b);
void			transform_matrix_cy(t_cylinder *cy);
t_vector		vector_transform(t_vector vector, t_cylinder *cy);
t_ray			ray_transform_cy(t_ray ray, t_cylinder *cy);
t_point			p3_add(t_point a, t_vector b);
int				plane_intersection(t_ray ray, t_plane plane,
					t_intersection *inter);
int				sphere_intersection(t_ray ray, t_sphere sphere,
					t_intersection *inter);
int				cylinder_intersection(t_ray ray, t_cylinder cy,
					t_intersection *inter);
int				cylinder_cap_intersection(t_ray ray_m, t_cylinder cy,
					t_plane cap_plane, double *current_t);
double			cylinder_side_intersection(t_ray r, t_cylinder cy);
int				cylinder_side_check(t_ray ray, t_ray ray_m,
					t_cylinder cy, t_intersection *inter);
int				cylinder_caps_check(t_ray ray, t_ray ray_m,
					t_cylinder cy, t_intersection *inter);
t_vector		calculate_cylinder_normal(t_ray ray, t_cylinder cy,
					double t, int hit_type);
int				plane_intersection_l(t_ray_light ray, t_plane plane,
					t_intersection *inter);
int				sphere_intersection_l(t_ray_light ray, t_sphere sphere,
					t_intersection *inter);
int				cylinder_intersection_l(t_ray_light ray, t_cylinder cy,
					t_intersection *inter);
int				cylinder_cap_intersection_l(t_ray_light ray_m, t_cylinder cy,
					t_plane cap_plane, double *current_t);
double			cylinder_side_intersection_l(t_ray_light r, t_cylinder cy);
int				cylinder_side_check_l(t_ray_light ray, t_ray_light ray_m,
					t_cylinder cy, t_intersection *inter);
int				cylinder_caps_check_l(t_ray_light ray, t_ray_light ray_m,
					t_cylinder cy, t_intersection *inter);
t_vector		calculate_cylinder_normal_l(t_ray_light ray, t_cylinder cy,
					double t, int hit_type);
t_vector		vector_transform_l(t_vector vector, t_cylinder *cy);
t_ray_light		ray_transform_cy_l(t_ray_light ray, t_cylinder *cy);

#endif
