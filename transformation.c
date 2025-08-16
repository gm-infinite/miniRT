/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:30:17 by emgenc            #+#    #+#             */
/*   Updated: 2025/08/16 14:21:48 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

// first is column, second is row.
void	transform_matrix(t_cylinder *cy)
{
	t_vector	new_x;
	t_vector	new_y;
	t_vector	new_z;

	new_y = vector(cy->direction.x, cy->direction.y, cy->direction.z);
	if (new_y.x < 0.9)
		new_x = vector_cross_product(new_y, vector(1, 0, 0));
	else
		new_x = vector_cross_product(new_y, vector(0, 0, 1));
	new_z = vector_cross_product(new_x, new_y);
	cy->matrix[0][0] = new_x.x;
	cy->matrix[0][1] = new_x.y;
	cy->matrix[0][2] = new_x.z;
	cy->matrix[1][0] = new_y.x;
	cy->matrix[1][1] = new_y.y;
	cy->matrix[1][2] = new_y.z;
	cy->matrix[2][0] = new_z.x;
	cy->matrix[2][1] = new_z.y;
	cy->matrix[2][2] = new_z.z;
}

t_vector	vector_transform(t_vector vector, t_cylinder *cy)
{
	t_vector	new_vector;

	new_vector.x = (cy->matrix[0][0] * vector.x)
		+ (cy->matrix[1][0] * vector.y) + (cy->matrix[2][0] * vector.z);
	new_vector.y = (cy->matrix[0][1] * vector.x)
		+ (cy->matrix[1][1] * vector.y) + (cy->matrix[2][1] * vector.z);
	new_vector.z = (cy->matrix[0][2] * vector.x)
		+ (cy->matrix[1][2] * vector.y) + (cy->matrix[2][2] * vector.z);
	return (new_vector);
}

t_ray	ray_transform(t_ray ray, t_cylinder *cy)
{
	t_ray	new_ray;

	new_ray.origin = vector_transform(ray.origin, cy);
	new_ray.direction = vector_normalize(vector_transform(ray.direction, cy));
	return (new_ray);
}
