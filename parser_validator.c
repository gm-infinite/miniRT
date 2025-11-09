/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:14:02 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 17:22:32 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

inline bool	validate_double(const char *str, void *out)
{
	double	*value;

	value = (double *)out;
	*value = ft_atof(str);
	return (isfinite(*value));
}

inline bool	validate_vector(const char *str, void *out)
{
	char		**parts;
	t_vector	*vec;

	vec = (t_vector *)out;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), false);
	vec->x = ft_atof(parts[0]);
	vec->y = ft_atof(parts[1]);
	vec->z = ft_atof(parts[2]);
	free_tokens(parts);
	return (isfinite(vec->x) && isfinite(vec->y) && isfinite(vec->z));
}

inline bool	validate_color(const char *str, void *out)
{
	char	**parts;
	t_color	*color;
	int		rgb[3];

	color = (t_color *)out;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), false);
	rgb[0] = ft_atoi(parts[0]);
	rgb[1] = ft_atoi(parts[1]);
	rgb[2] = ft_atoi(parts[2]);
	free_tokens(parts);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (false);
	color->r = rgb[0];
	color->g = rgb[1];
	color->b = rgb[2];
	return (true);
}

inline bool	validate_normal(const char *str, void *out)
{
	t_vector	*vec;
	double		magnitude;

	vec = (t_vector *)out;
	if (!validate_vector(str, vec))
		return (false);
	magnitude = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
	if (magnitude < 0.99 || magnitude > 1.01)
		return (false);
	*vec = v3_norm(*vec);
	return (true);
}

inline bool	validate_ratio(const char *str, void *out)
{
	double	*value;

	value = (double *)out;
	if (!validate_double(str, value))
		return (false);
	return (*value >= 0.0 && *value <= 1.0);
}
