/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:23:29 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/11/02 13:32:31 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static int	is_in_shadow(t_data *data, t_point point_intsc,
	t_vector dir_l, double dis_l)
{
	t_ray			sr;
	t_intersection	s_intsc;
	int				i;

	sr.origin = p3_add(point_intsc, v3_mult(0.001, dir_l));
	sr.direction = dir_l;
	i = -1;
	while (++i < data->scene.num_objects)
	{
		s_intsc.t = -1.0;
		if (data->scene.all_objects[i].type == PLANE
			&& plane_intersection(sr, data->scene.all_objects[i].object.plane,
				&s_intsc) && s_intsc.t > 0 && s_intsc.t < dis_l)
			return (1);
		else if (data->scene.all_objects[i].type == SPHERE
			&& sphere_intersection(sr, data->scene.all_objects[i].object.sphere,
				&s_intsc) && s_intsc.t > 0 && s_intsc.t < dis_l)
			return (1);
		else if (data->scene.all_objects[i].type == CYLINDER
			&& cylinder_intersection(sr,
				data->scene.all_objects[i].object.cylinder,
				&s_intsc) && s_intsc.t > 0 && s_intsc.t < dis_l)
			return (1);
	}
	return (0);
}

t_intersection	find_closest_intersection(t_data *data, t_ray ray)
{
	t_intersection	intersec;
	int				i;

	i = 0;
	intersec.t = -1.0;
	intersec.color = color(0, 0, 0);
	while (i < data->scene.num_objects)
	{
		if (data->scene.all_objects[i].type == PLANE)
			plane_intersection(ray,
				data->scene.all_objects[i].object.plane, &intersec);
		else if (data->scene.all_objects[i].type == SPHERE)
			sphere_intersection(ray,
				data->scene.all_objects[i].object.sphere, &intersec);
		else if (data->scene.all_objects[i].type == CYLINDER)
			cylinder_intersection(ray,
				data->scene.all_objects[i].object.cylinder, &intersec);
		i++;
	}
	return (intersec);
}

t_color	calculate_ambient_lighting(t_color object_color, t_data *data)
{
	return (light_hit_color(object_color,
			data->scene.ambient_light.color,
			data->scene.ambient_light.intensity));
}

t_color	calculate_diffuse_lighting(t_data *data, t_color object_color,
			t_point point_intsc, t_vector surface_normal)
{
	t_vector	light_vec;
	double		dis_light;
	t_vector	dir_light;
	double		diffuse_factor;

	light_vec = point_substract(data->scene.light.position, point_intsc);
	dis_light = v3_len(light_vec);
	dir_light = v3_norm(light_vec);
	if (is_in_shadow(data, point_intsc, dir_light, dis_light))
		return (color(0, 0, 0));
	diffuse_factor = v3_dot(surface_normal, dir_light);
	if (diffuse_factor < 0)
		diffuse_factor = 0;
	return (light_hit_color(object_color, color(255, 255, 255),
			diffuse_factor * data->scene.light.intensity));
}
