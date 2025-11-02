/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:50:56 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/11/02 13:23:22 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

int	color_to_int(t_color color)
{
	return ((0)
		| (color.r & 0xff) << 16
		| (color.g & 0xff) << 8
		| (color.b & 0xff));
}

//on mandotory light color is always white (255,255,255)
t_color	light_hit_color(t_color object_color,
	t_color light_color, double intensity)
{
	t_color	result_color;

	result_color.r = (unsigned char)(object_color.r
			* light_color.r / 255.0 * intensity);
	result_color.g = (unsigned char)(object_color.g
			* light_color.g / 255.0 * intensity);
	result_color.b = (unsigned char)(object_color.b
			* light_color.b / 255.0 * intensity);
	return (result_color);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color			result;
	unsigned int	overflow;

	overflow = (unsigned int)c1.r + (unsigned int)c2.r;
	if (overflow > 255)
		overflow = 255;
	result.r = (unsigned char)overflow;
	overflow = (unsigned int)c1.g + (unsigned int)c2.g;
	if (overflow > 255)
		overflow = 255;
	result.g = (unsigned char)overflow;
	overflow = (unsigned int)c1.b + (unsigned int)c2.b;
	if (overflow > 255)
		overflow = 255;
	result.b = (unsigned char)overflow;
	return (result);
}
