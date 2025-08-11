/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:41:37 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:08:58 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_normilize(t_vector v)
{
	return (vector_constant_divide(vector_length(v), v));
}

double	vector_dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vector_cross_product(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = (v1.y * v2.z) - (v1.z * v2.y);
	ret.y = (v1.z * v2.x) - (v1.x * v2.z);
	ret.z = (v1.x * v2.y) - (v2.x * v1.y);
	return (ret);
}

t_vector	vector(double x, double y, double z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}
