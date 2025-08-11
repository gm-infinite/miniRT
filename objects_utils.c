/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:24:05 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/11 22:48:07 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdbool.h>

bool	is_valid_intersection(t_intersection_point intersection)
{
	if (intersection.surface_normal.x <= T_ZERO_THRESHOLD
		&& intersection.surface_normal.y <= T_ZERO_THRESHOLD
		&& intersection.surface_normal.z <= T_ZERO_THRESHOLD)
		return (false);
	return (true);
}
