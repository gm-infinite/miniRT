/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_constructors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:45:44 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/11/02 13:35:53 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_intersection	intersection_constructor(double t, t_vector sf_normal,
					t_color color)
{
	t_intersection	ret;

	ret.t = t;
	ret.sf_normal = sf_normal;
	ret.color = color;
	return (ret);
}

t_plane	plane(t_vector direction, t_point origin)
{
	t_plane	ret;

	ret.direction = direction;
	ret.origin = origin;
	return (ret);
}
