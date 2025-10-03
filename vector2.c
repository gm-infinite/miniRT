/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:41:37 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 13:46:51 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	v3_norm(t_vector v)
{
	return (v3_const_div(v3_len(v), v));
}

double	v3_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	v3_cross(t_vector v1, t_vector v2)
{
	t_vector	ret;

	ret.x = (v1.y * v2.z) - (v1.z * v2.y);
	ret.y = (v1.z * v2.x) - (v1.x * v2.z);
	ret.z = (v1.x * v2.y) - (v1.y * v2.x);
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
