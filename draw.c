/* ***********************	shadow_intersec.t = -1.0;************************************************* */
/*   		plane_intersection(ray, data->scene.all_objects[i].object.plane, &intersec);   		sphere_intersection(ray, data->scene.all_objects[i].object.sphere, &intersec);   		cylinder_intersection(ray, data->scene.all_objects[i].object.cylinder, &intersec);                                                             */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:23:29 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/09/07 16:03:40 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

int is_in_shadow(t_data *data, t_point intersection_point, t_vector light_direction, double light_distance)
{
	t_ray shadow_ray;
	t_intersection shadow_intersec;
	int i;

	shadow_ray.origin = p3_add(intersection_point, v3_mult(0.001, light_direction));
	shadow_ray.direction = light_direction;
	i = -1;
	while (++i < data->scene.num_objects)
	{
		shadow_intersec.t = -1.0;
		if (data->scene.all_objects[i].type == PLANE
			&& plane_intersection(shadow_ray, data->scene.all_objects[i].object.plane, &shadow_intersec)
			&& shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
			return (1);
		else if (data->scene.all_objects[i].type == SPHERE
			&& sphere_intersection(shadow_ray, data->scene.all_objects[i].object.sphere, &shadow_intersec)
			&& shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
			return (1);
		else if (data->scene.all_objects[i].type == CYLINDER
			&& cylinder_intersection(shadow_ray, data->scene.all_objects[i].object.cylinder, &shadow_intersec)
			&& shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
			return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int pixel_color(t_data *data, double px, double py)
{
	t_vector v_forward;
	t_vector v_right;
	t_vector v_up;
	
	v_forward = data->scene.camera.direction;
	v_right = v3_norm(v3_cross(v_forward, vector(0,1,0)));
	v_up = v3_cross(v_right, v_forward);
	
	double distance_to_viewport;
	distance_to_viewport = (W_HEIGHT / 2.0) / tan((M_PI * data->scene.camera.fov) / 360.0);

	t_ray ray;
	ray.origin = data->scene.camera.origin;
	ray.direction = v3_norm(v3_add(v3_mult(distance_to_viewport, v_forward), v3_add(v3_mult(px * W_WIDTH / 2.0, v_right), v3_mult(py * W_HEIGHT / 2.0, v_up))));

	t_intersection intersec;
	int i;
	i = 0;
	intersec.t = -1.0;
	intersec.color = (t_color){0, 0, 0};

	while (i < data->scene.num_objects)
	{
		if (data->scene.all_objects[i].type == PLANE)
		{
			plane_intersection(ray, data->scene.all_objects[i].object.plane, &intersec);
		}
		else if (data->scene.all_objects[i].type == SPHERE)
		{
			sphere_intersection(ray, data->scene.all_objects[i].object.sphere, &intersec);
		}
		else if (data->scene.all_objects[i].type == CYLINDER)
		{
			cylinder_intersection(ray, data->scene.all_objects[i].object.cylinder, &intersec);
		}
		i++;
	}

	

	t_color object_color;
	if (intersec.t > 0)
		object_color = intersec.color;
	else
		object_color = data->scene.ambient_light.color;
	
	t_color final_color = light_hit_color(object_color, 
	                                     data->scene.ambient_light.color,
	                                     data->scene.ambient_light.intensity);
	
	if (intersec.t > 0)
	{
		t_point intersection_point = p3_add(ray.origin, v3_mult(intersec.t, ray.direction));
		
		t_vector light_vec = point_substract(data->scene.light.position, intersection_point);
		double light_distance = v3_len(light_vec);
		t_vector light_direction = v3_norm(light_vec);
		
		if (!is_in_shadow(data, intersection_point, light_direction, light_distance))
		{
			t_vector surface_normal = intersec.sf_normal;
			
			double diffuse_factor = v3_dot(surface_normal, light_direction);
			
			if (diffuse_factor < 0)
				diffuse_factor = 0;
			
			t_color diffuse_color = light_hit_color(object_color, 
			                                       (t_color){255, 255, 255}, 
			                                       diffuse_factor * data->scene.light.intensity);
			
			final_color = color_add(final_color, diffuse_color);
		}
	}
	
	return color_to_int(final_color);
}

void drawscene(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < W_WIDTH)
	{
		y = -1;
		while (++y < W_HEIGHT)
			my_mlx_pixel_put(data, x, y,
				pixel_color(data,
					((2 * x / (double)W_WIDTH) - 1),
					-((2 * y / (double)W_HEIGHT) - 1)));
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
