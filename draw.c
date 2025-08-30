/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:23:29 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 14:33:18 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	t_ray ray;
	ray.origin = data->scene.camera.origin;
	ray.direction = vector_normalize(vector_add(v_forward, vector_add(vector_multiply(px, v_right), vector_multiply(py, v_up))));

	double t;
	t_intersection intersec;
	int i;
	i = 0;
	t = -1.0;
	intersec.t = -1.0;
	intersec.object = NULL;
	intersec.type = -1;

	while (i < data->scene.num_objects)
	{
		if (data->scene.all_objects[i].type == PLANE)
			t = plane_intersection(ray, data->scene.all_objects[i].object.plane);
		else if (data->scene.all_objects[i].type == SPHERE)
			t = sphere_intersection(ray, data->scene.all_objects[i].object.sphere);
		else if (data->scene.all_objects[i].type == CYLINDER)
			t = cylinder_intersection(ray, data->scene.all_objects[i].object.cylinder);
		if (t > 0 && (intersec.t < 0 || t < intersec.t))
		{
			intersec.t = t;
			intersec.object = &data->scene.all_objects[i].object;
			intersec.type = data->scene.all_objects[i].type;
		}
		i++;
	}
	

	int final_color = color_to_int(data->scene.ambient_light.color);

	if (intersec.type == PLANE)
		final_color = color_to_int((intersec.object->plane).color);
	else if (intersec.type == SPHERE)
		final_color = color_to_int((intersec.object->sphere).color);
	else if (intersec.type == CYLINDER)
		final_color = color_to_int((intersec.object->cylinder).color);
	return (final_color);
}

void drawscene(t_data *data)
{
	int x;
	int y;

	x = -1;
	while (++x < W_WIDTH)
	{
		y = -1;
		while (++y < W_HEIGHT)
			my_mlx_pixel_put(data, x, y, pixel_color(data, ((2 * x / (double)W_WIDTH) - 1), -((2 * y / (double)W_HEIGHT) - 1)));
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
