/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:45:44 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:08:42 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_ray	ray(t_vector direction, t_point origin)
{
	t_ray	ret;

	ret.direction = direction;
	ret.origin = origin;
	ret.t = 0;
	return (ret);
}

t_plane	plane(t_vector direction, t_point origin)
{
	t_plane	ret;

	ret.direction = direction;
	ret.origin = origin;
	return (ret);
}

t_sphere	sphere(t_point origin, double radius)
{
	t_sphere	ret;

	ret.origin = origin;
	ret.radius = radius;
	return (ret);
}

t_cylinder	cylinder(t_vector normal, t_point origin,
					double radius, double height)
{
	t_cylinder	ret;

	ret.normal = normal;
	ret.origin = origin;
	ret.radius = radius;
	ret.height = height;
	return (ret);
}
