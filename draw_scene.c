/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:23:29 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 15:11:12 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

t_ray	create_camera_ray(t_data *data, double px, double py)
{
	t_vector	v_forward;
	t_ray		ray;
	double		distance_to_viewport;

	v_forward = data->scene.camera.direction;
	distance_to_viewport = (W_HEIGHT / 2.0)
		/ tan((M_PI * data->scene.camera.fov) / 360.0);
	ray.direction = v3_norm(v3_add(v3_mult(distance_to_viewport, v_forward),
					v3_add(vector(0, 0, px * W_WIDTH / 2.0),
					vector(0, py * W_HEIGHT / 2.0, 0))));
	return (ray);
}

int	pixel_color(t_data *data, double px, double py)
{
	t_ray			ray;
	t_intersection	intersec;
	t_color			object_color;
	t_color			final_color;
	t_point			point_intsc;

	ray = create_camera_ray(data, px, py);
	intersec = find_closest_intersection(data, ray);
	if (intersec.t > 0)
		object_color = intersec.color;
	else
		object_color = data->scene.ambient_light.color;
	final_color = calculate_ambient_lighting(object_color, data);
	if (intersec.t > 0)
	{
		point_intsc = v3_mult(intersec.t, ray.direction);
		final_color = color_add(final_color,
				calculate_diffuse_lighting(data, object_color,
					point_intsc, intersec.sf_normal));
	}
	return (color_to_int(final_color));
}

void	drawscene(t_data *data)
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
