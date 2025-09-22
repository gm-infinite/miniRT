/* ************************************************************************** */
/*                                                                            */
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

// Check if a point is in shadow by casting a ray towards the light
int is_in_shadow(t_data *data, t_point intersection_point, t_vector light_direction, double light_distance)
{
	t_ray shadow_ray;
	t_intersection shadow_intersec;
	int i;

	// Create shadow ray from intersection point towards light
	shadow_ray.origin = point_add(intersection_point, vector_multiply(0.001, light_direction)); // Small offset to avoid self-intersection
	shadow_ray.direction = light_direction;

	// Check if shadow ray hits any object before reaching the light
	i = 0;
	while (i < data->scene.num_objects)
	{
		shadow_intersec.t = -1.0;
		shadow_intersec.type = -1;

		if (data->scene.all_objects[i].type == PLANE)
		{
			if (plane_intersection(shadow_ray, data->scene.all_objects[i].object.plane, &shadow_intersec))
			{
				if (shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
					return (1); // In shadow
			}
		}
		else if (data->scene.all_objects[i].type == SPHERE)
		{
			if (sphere_intersection(shadow_ray, data->scene.all_objects[i].object.sphere, &shadow_intersec))
			{
				if (shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
					return (1); // In shadow
			}
		}
		else if (data->scene.all_objects[i].type == CYLINDER)
		{
			if (cylinder_intersection(shadow_ray, data->scene.all_objects[i].object.cylinder, &shadow_intersec))
			{
				if (shadow_intersec.t > 0 && shadow_intersec.t < light_distance)
					return (1); // In shadow
			}
		}
		i++;
	}
	return (0); // Not in shadow
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
	v_right = vector_normalize(vector_cross_product(v_forward, vector(0,1,0)));
	v_up = vector_cross_product(v_right, v_forward);
	
	double distance_to_viewport;
	distance_to_viewport = (W_HEIGHT / 2.0) / tan((M_PI * data->scene.camera.fov) / 360.0);

	t_ray ray;
	ray.origin = data->scene.camera.origin;
	    ray.direction = vector_normalize(vector_add(
        vector_multiply(distance_to_viewport, v_forward), 
        vector_add(
            vector_multiply(px * W_WIDTH / 2.0, v_right), 
            vector_multiply(py * W_HEIGHT / 2.0, v_up)
        )
    ));

	t_intersection intersec;
	int i;
	i = 0;
	intersec.t = -1.0;
	intersec.object = NULL;
	intersec.type = -1;

	while (i < data->scene.num_objects)
	{
		if (data->scene.all_objects[i].type == PLANE)
		{
			if (plane_intersection(ray, data->scene.all_objects[i].object.plane, &intersec))
				intersec.object = &data->scene.all_objects[i].object;
		}
		else if (data->scene.all_objects[i].type == SPHERE)
		{
			if (sphere_intersection(ray, data->scene.all_objects[i].object.sphere, &intersec))
				intersec.object = &data->scene.all_objects[i].object;
		}
		else if (data->scene.all_objects[i].type == CYLINDER)
		{
			if (cylinder_intersection(ray, data->scene.all_objects[i].object.cylinder, &intersec))
				intersec.object = &data->scene.all_objects[i].object;
		}
		i++;
	}

	

	t_color object_color;
	if (intersec.type == PLANE)
	    object_color = (intersec.object->plane).color;
	else if (intersec.type == SPHERE)
	    object_color = (intersec.object->sphere).color;
	else if (intersec.type == CYLINDER)
	    object_color = (intersec.object->cylinder).color;
	else
		object_color = data->scene.ambient_light.color;
	
	// Apply ambient lighting first
	t_color final_color = light_hit_color(object_color, 
	                                     data->scene.ambient_light.color,
	                                     data->scene.ambient_light.intensity);
	
	// If we hit an object, apply diffuse lighting
	if (intersec.t > 0)
	{
		// Calculate intersection point
		t_point intersection_point = point_add(ray.origin, vector_multiply(intersec.t, ray.direction));
		
		// Calculate light direction and distance
		t_vector light_vec = point_substract(data->scene.light.position, intersection_point);
		double light_distance = vector_length(light_vec);
		t_vector light_direction = vector_normalize(light_vec);
		
		// Check if in shadow
		if (!is_in_shadow(data, intersection_point, light_direction, light_distance))
		{
			// Get surface normal from intersection
			t_vector surface_normal = intersec.sf_normal;
			
			// Calculate diffuse factor using Lambert's cosine law
			double diffuse_factor = vector_dot_product(surface_normal, light_direction);
			
			// Clamp to [0,1] - negative means light is behind surface
			if (diffuse_factor < 0)
				diffuse_factor = 0;
			
			// Apply diffuse lighting
			t_color diffuse_color = light_hit_color(object_color, 
			                                       (t_color){255, 255, 255}, 
			                                       diffuse_factor * data->scene.light.intensity);
			
			// Add diffuse lighting to ambient
			final_color = color_add(final_color, diffuse_color);
		}
		// If in shadow, only ambient lighting is applied
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
