/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection_light2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

int	cylinder_side_check_l(t_ray_light ray, t_ray_light ray_m, t_cylinder cy,
		t_intersection *inter)
{
	double	side_t;

	side_t = cylinder_side_intersection_l(ray_m, cy);
	if (side_t > 0 && (inter->t < 0 || side_t < inter->t))
	{
		*inter = intersection_constructor(side_t, calculate_cylinder_normal_l(
					ray, cy, side_t, 0), cy.color);
		return (1);
	}
	return (0);
}

int	cylinder_caps_check_l(t_ray_light ray, t_ray_light ray_m, t_cylinder cy,
		t_intersection *inter)
{
	double	cap_t;
	int		found;

	found = 0;
	cap_t = -1;
	if (cylinder_cap_intersection_l(ray_m, cy,
			plane(vector(0, 1, 0), vector(0, cy.h / 2, 0)), &cap_t)
		&& cap_t > 0 && (inter->t < 0 || cap_t < inter->t))
	{
		*inter = intersection_constructor(cap_t, calculate_cylinder_normal_l(
					ray, cy, cap_t, 1), cy.color);
		found = 1;
	}
	if (cylinder_cap_intersection_l(ray_m, cy,
			plane(vector(0, -1, 0), vector(0, -cy.h / 2, 0)), &cap_t)
		&& cap_t > 0 && (inter->t < 0 || cap_t < inter->t))
	{
		*inter = intersection_constructor(cap_t, calculate_cylinder_normal_l(
					ray, cy, cap_t, 2), cy.color);
		found = 1;
	}
	return (found);
}

int	cylinder_intersection_l(t_ray_light ray, t_cylinder cy, t_intersection *inter)
{
	t_ray_light	ray_m;
	int			side_hit;
	int			cap_hit;

	ray_m = ray_transform_cy_l(ray, &cy);
	side_hit = cylinder_side_check_l(ray, ray_m, cy, inter);
	cap_hit = cylinder_caps_check_l(ray, ray_m, cy, inter);
	return (side_hit || cap_hit);
}