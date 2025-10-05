/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:30:17 by emgenc            #+#    #+#             */
/*   Updated: 2025/08/30 13:35:43 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <math.h>

// first is column, second is row.
void	transform_matrix_cy(t_cylinder *cy)
{
	t_vector	new_x;
	t_vector	new_y;
	t_vector	new_z;
	t_vector	temp;

	new_y = v3_norm(cy->direction);
	if (fabs(new_y.y) < 0.99)
		temp = vector(0, 1, 0);
	else
		temp = vector(1, 0, 0);
	new_x = v3_norm(v3_cross(temp, new_y));
	new_z = v3_cross(new_y, new_x);
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

// dot product with basis vectors (columns) = transpose multiplication
t_vector	vector_transform(t_vector vector, t_cylinder *cy)
{
	t_vector	new_vector;

	new_vector.x = v3_dot(vector, (t_vector){
			cy->matrix[0][0], cy->matrix[0][1], cy->matrix[0][2]});
	new_vector.y = v3_dot(vector, (t_vector){
			cy->matrix[1][0], cy->matrix[1][1], cy->matrix[1][2]});
	new_vector.z = v3_dot(vector, (t_vector){
			cy->matrix[2][0], cy->matrix[2][1], cy->matrix[2][2]});
	return (new_vector);
}

t_ray	ray_transform_cy(t_ray ray, t_cylinder *cy)
{
	t_ray	new_ray;

	cy->ray_or = vector_transform(v3_neg(cy->origin), cy);
	new_ray.direction = v3_norm(vector_transform(ray.direction, cy));
	return (new_ray);
}
