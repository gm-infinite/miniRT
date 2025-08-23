/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:15:53 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/23 12:32:23 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

int				color_to_int(t_color color);
t_color			int_to_color(int color);
t_color			color_scale(t_color color, double factor);
t_color			light_hit_color(t_color object_color, double intensity);
t_color			color_add(t_color c1, t_color c2);

#endif
