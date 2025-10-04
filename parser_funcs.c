/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:02:40 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/04 12:55:37 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

static int	validate_vector_finite(t_vector v)
{
	return (isfinite(v.x) && isfinite(v.y) && isfinite(v.z));
}

static int	validate_color(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	validate_normalized(double x, double y, double z)
{
	if (!isfinite(x) || !isfinite(y) || !isfinite(z))
		return (0);
	return ((x*x + y*y + z*z - 1) >= -0.01 && (x*x + y*y + z*z - 1) <= 0.01);
}

int	validate_coords(char **coords)
{
	if (!coords || !coords[0] || !coords[1] || !coords[2])
		return (0);
	if (coords[3] != NULL)
		return (0);
	return (1);
}

static int	validate_finite(double value)
{
	return (isfinite(value));
}

static void	cleanup_split_three(char **s1, char **s2, char **s3)
{
	free_split(s1);
	free_split(s2);
	free_split(s3);
}

int	parse_sp(t_data *data, char *line, unsigned short *current_idx)
{
	t_sphere	temp_sphere;
	char		**split[3];
	double		diameter;

	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || !split[0][3]
		|| split[0][4] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][1], ',');
	split[2] = ft_split(split[0][3], ',');
	if (!validate_coords(split[1]) || !validate_coords(split[2]))
		return (cleanup_split_three(split[0], split[1], split[2]), 0);
	temp_sphere.origin = vector(ft_atof(split[1][0]),
			ft_atof(split[1][1]), ft_atof(split[1][2]));
	if (!validate_vector_finite(temp_sphere.origin))
		return (cleanup_split_three(split[0], split[1], split[2]), 0);
	diameter = ft_atof(split[0][2]);
	if (!validate_finite(diameter) || diameter <= 0.0)
		return (cleanup_split_three(split[0], split[1], split[2]), 0);
	temp_sphere.radius = diameter / 2.0;
	temp_sphere.color = (t_color){ft_atoi(split[2][0]),
		ft_atoi(split[2][1]), ft_atoi(split[2][2])};
	if (!validate_color(temp_sphere.color.r, temp_sphere.color.g,
			temp_sphere.color.b))
		return (cleanup_split_three(split[0], split[1], split[2]), 0);
	data->scene.all_objects[*current_idx].type = SPHERE;
	data->scene.all_objects[*current_idx].object.sphere = temp_sphere;
	(*current_idx)++;
	return (cleanup_split_three(split[0], split[1], split[2]), 1);
}

static int	validate_plane_data(char **split[4], t_plane *plane)
{
	double		x;
	double		y;
	double		z;
	t_vector	dir;

	x = ft_atof(split[2][0]);
	y = ft_atof(split[2][1]);
	z = ft_atof(split[2][2]);
	if (!validate_normalized(x, y, z))
		return (0);
	dir = v3_norm(vector(x, y, z));
	plane->direction = v3_norm(dir);
	plane->origin = vector(ft_atof(split[1][0]),
			ft_atof(split[1][1]), ft_atof(split[1][2]));
	if (!validate_vector_finite(plane->origin))
		return (0);
	plane->color = (t_color){ft_atoi(split[3][0]),
		ft_atoi(split[3][1]), ft_atoi(split[3][2])};
	if (!validate_color(plane->color.r, plane->color.g, plane->color.b))
		return (0);
	return (1);
}

int	parse_pl(t_data *data, char *line, unsigned short *current_idx)
{
	t_plane	temp_plane;
	char	**split[4];

	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || !split[0][3]
		|| split[0][4] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][1], ',');
	split[2] = ft_split(split[0][2], ',');
	split[3] = ft_split(split[0][3], ',');
	if (!validate_coords(split[1]) || !validate_coords(split[2])
		|| !validate_coords(split[3]))
		return (cleanup_split_three(split[0], split[1], split[2]),
			free_split(split[3]), 0);
	if (!validate_plane_data(split, &temp_plane))
		return (cleanup_split_three(split[0], split[1], split[2]),
			free_split(split[3]), 0);
	data->scene.all_objects[*current_idx].type = PLANE;
	data->scene.all_objects[*current_idx].object.plane = temp_plane;
	(*current_idx)++;
	cleanup_split_three(split[0], split[1], split[2]);
	free_split(split[3]);
	return (1);
}

static int	validate_cy_data(char **split[5], t_cylinder *cy)
{
	double		x;
	double		y;
	double		z;
	t_vector	dir;

	x = ft_atof(split[2][0]);
	y = ft_atof(split[2][1]);
	z = ft_atof(split[2][2]);
	if (!validate_normalized(x, y, z))
		return (0);
	dir = v3_norm(vector(x, y, z));
	cy->direction = v3_norm(dir);
	cy->origin = vector(ft_atof(split[1][0]), ft_atof(split[1][1]),
			ft_atof(split[1][2]));
	if (!validate_vector_finite(cy->origin))
		return (0);
	cy->radius = ft_atof(split[0][3]) / 2.0;
	cy->h = ft_atof(split[0][4]);
	if (!validate_finite(cy->radius) || !validate_finite(cy->h)
		|| cy->radius <= 0.0 || cy->h <= 0.0)
		return (0);
	cy->color = (t_color){ft_atoi(split[3][0]), ft_atoi(split[3][1]),
		ft_atoi(split[3][2])};
	if (!validate_color(cy->color.r, cy->color.g, cy->color.b))
		return (0);
	return (1);
}

int	parse_cy(t_data *data, char *line, unsigned short *current_idx)
{
	t_cylinder	cy;
	char		**split[5];

	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || !split[0][3]
		|| !split[0][4] || !split[0][5] || split[0][6] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][1], ',');
	split[2] = ft_split(split[0][2], ',');
	split[3] = ft_split(split[0][5], ',');
	if (!validate_coords(split[1]) || !validate_coords(split[2])
		|| !validate_coords(split[3]))
		return (cleanup_split_three(split[0], split[1], split[2]),
			free_split(split[3]), 0);
	if (!validate_cy_data(split, &cy))
		return (cleanup_split_three(split[0], split[1], split[2]),
			free_split(split[3]), 0);
	transform_matrix_cy(&cy);
	data->scene.all_objects[*current_idx].type = CYLINDER;
	data->scene.all_objects[*current_idx].object.cylinder = cy;
	(*current_idx)++;
	cleanup_split_three(split[0], split[1], split[2]);
	free_split(split[3]);
	return (1);
}

int	parse_lightsrc(t_data *data, char *line, unsigned short *current_idx)
{
	char		**split[3];
	t_vector	pos;

	(void)current_idx;
	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || !split[0][3]
		|| split[0][4] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][1], ',');
	split[2] = ft_split(split[0][3], ',');
	if (!validate_coords(split[1]) || !validate_coords(split[2]))
		return (free_split(split[0]), free_split(split[1]),
			free_split(split[2]), 0);
	pos = vector(ft_atof(split[1][0]),
			ft_atof(split[1][1]), ft_atof(split[1][2]));
	if (!validate_vector_finite(pos))
		return (free_split(split[1]), free_split(split[2]),
			free_split(split[0]), 0);
	data->scene.light.position = pos;
	data->scene.light.intensity = ft_atof(split[0][2]);
	if (!validate_finite(data->scene.light.intensity)
		|| data->scene.light.intensity < 0.0
		|| data->scene.light.intensity > 1.0)
		return (free_split(split[1]), free_split(split[2]),
			free_split(split[0]), 0);
	free_split(split[1]);
	free_split(split[2]);
	free_split(split[0]);
	return (1);
}

int	parse_ambient(t_data *data, char *line, unsigned short *current_idx)
{
	char	**split[2];

	(void)current_idx;
	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || split[0][3] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][2], ',');
	if (!validate_coords(split[1]))
		return (free_split(split[0]), free_split(split[1]), 0);
	data->scene.ambient_light.intensity = ft_atof(split[0][1]);
	data->scene.ambient_light.color = (t_color){ft_atoi(split[1][0]),
		ft_atoi(split[1][1]), ft_atoi(split[1][2])};
	if (!validate_finite(data->scene.ambient_light.intensity)
		|| data->scene.ambient_light.intensity < 0.0
		|| data->scene.ambient_light.intensity > 1.0)
		return (free_split(split[1]), free_split(split[0]), 0);
	if (!validate_color(data->scene.ambient_light.color.r,
			data->scene.ambient_light.color.g,
			data->scene.ambient_light.color.b))
		return (free_split(split[1]), free_split(split[0]), 0);
	free_split(split[1]);
	free_split(split[0]);
	return (1);
}
