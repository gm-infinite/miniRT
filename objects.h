/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:55:28 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:07:51 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "vector.h"

typedef t_coordinates_3d	t_point;

typedef struct s_ray
{
	t_vector	direction;
	t_point		origin;
	double		t;
}	t_ray;

typedef struct s_plane
{
	t_vector	direction;
	t_point		origin;
}	t_plane;

typedef struct s_sphere
{
	t_point		origin;
	double		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	normal;
	t_point		origin;
	double		radius;
	double		height;
}	t_cylinder;

#endif
