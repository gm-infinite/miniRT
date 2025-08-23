/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:23:29 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/23 12:40:04 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int pixel_color(t_data *data, int x, int y)
{
	//t_ray	ray;
	//t_color	color;
	(void)x;
	(void)y;

	//ray = get_ray_through_pixel(x, y, &data->scene.camera);
	//color = trace_ray(ray, &data->scene);
	//return (color_to_int(color.r, color.g, color.b));
	return (color_to_int(color_scale(data->scene.ambient_light.color, data->scene.ambient_light.intensity)));
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
			my_mlx_pixel_put(data, x, y, pixel_color(data, x, y));
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
