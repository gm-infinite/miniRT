/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_intersection2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:11:11 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/11/02 13:31:18 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

static int	cylinder_side_check(t_ray ray, t_ray ray_m, t_cylinder cy,
		t_intersection *inter)
{
	double	side_t;

	side_t = cylinder_side_intersection(ray_m, cy);
	if (side_t > 0 && (inter->t < 0 || side_t < inter->t))
	{
		*inter = intersection_constructor(side_t, calculate_cylinder_normal(
					ray, cy, side_t, 0), cy.color);
		return (1);
	}
	return (0);
}

static int	cylinder_caps_check(t_ray ray, t_ray ray_m, t_cylinder cy,
		t_intersection *inter)
{
	double	cap_t;
	int		found;

	found = 0;
	cap_t = -1;
	if (cylinder_cap_intersection(ray_m, cy,
			plane(vector(0, 1, 0), vector(0, cy.h / 2, 0)), &cap_t)
		&& cap_t > 0 && (inter->t < 0 || cap_t < inter->t))
	{
		*inter = intersection_constructor(cap_t, calculate_cylinder_normal(
					ray, cy, cap_t, 1), cy.color);
		found = 1;
	}
	if (cylinder_cap_intersection(ray_m, cy,
			plane(vector(0, -1, 0), vector(0, -cy.h / 2, 0)), &cap_t)
		&& cap_t > 0 && (inter->t < 0 || cap_t < inter->t))
	{
		*inter = intersection_constructor(cap_t, calculate_cylinder_normal(
					ray, cy, cap_t, 2), cy.color);
		found = 1;
	}
	return (found);
}

int	cylinder_intersection(t_ray ray, t_cylinder cy, t_intersection *inter)
{
	t_ray	ray_m;
	int		side_hit;
	int		cap_hit;

	ray_m = ray_transform_cy(ray, &cy);
	side_hit = cylinder_side_check(ray, ray_m, cy, inter);
	cap_hit = cylinder_caps_check(ray, ray_m, cy, inter);
	return (side_hit || cap_hit);
}
