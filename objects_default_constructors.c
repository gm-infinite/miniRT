/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_default_constructors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:15:22 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 12:55:24 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_ray	ray_default(void)
{
	return (ray(vector(0, 0, 0), vector(0, 0, 0)));
}

t_plane	plane_default(void)
{
	return (plane(vector(0, 0, 0), vector(0, 0, 0)));
}

t_sphere	sphere_default(void)
{
	return (sphere(vector(0, 0, 0), 0));
}

t_cylinder	cylinder_default(void)
{
	return (cylinder(vector(0, 0, 0), vector(0, 0, 0), 0, 0));
}
