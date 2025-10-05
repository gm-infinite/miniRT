/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:16:34 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:16:36 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

bool	validate_fov(const char *str, void *out)
{
	double	*fov;

	fov = (double *)out;
	if (!validate_double(str, fov))
		return (false);
	if (*fov <= 0.0 || *fov >= 180.0)
		return (false);
	if (*fov < 0.1)
		*fov = 0.1;
	if (*fov > 179.9)
		*fov = 179.9;
	return (true);
}

bool	validate_positive(const char *str, void *out)
{
	double	*value;

	value = (double *)out;
	if (!validate_double(str, value))
		return (false);
	return (*value > 0.0);
}
