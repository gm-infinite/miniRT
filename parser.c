/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/04 14:53:41 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

static void	count_elements(char *line, unsigned long long *counts,
	t_data *data)
{
	if (is_empty_line(line))
		return ;
	if (ft_strncmp(line, "C ", 2) == 0)
		counts[0]++;
	else if (ft_strncmp(line, "A ", 2) == 0)
		counts[1]++;
	else if (ft_strncmp(line, "L ", 2) == 0)
		counts[2]++;
	else if (ft_strncmp(line, "sp ", 3) == 0
		|| ft_strncmp(line, "pl ", 3) == 0
		|| ft_strncmp(line, "cy ", 3) == 0)
		data->scene.num_objects++;
}

bool	permissible_count(t_data *data, int fd)
{
	unsigned long long	counts[3];
	char				*line;

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	data->scene.num_objects = 0;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		count_elements(line, counts, data);
		free(line);
		line = get_next_line(fd, 0);
	}
	line = get_next_line(fd, -1);
	if (line)
		free(line);
	if (counts[0] != 1 || counts[2] != 1 || counts[1] != 1)
		return (false);
	return (true);
}

static int	validate_camera_data(char **split[3], t_camera *cam)
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
	cam->direction = v3_norm(dir);
	cam->origin = vector(ft_atof(split[1][0]),
			ft_atof(split[1][1]), ft_atof(split[1][2]));
	if (!isfinite(cam->origin.x) || !isfinite(cam->origin.y)
		|| !isfinite(cam->origin.z))
		return (0);
	cam->fov = ft_atof(split[0][3]);
	if (!isfinite(cam->fov) || cam->fov < 0 || cam->fov > 180)
		return (0);
	cam->fov = cam->fov * (cam->fov < 179.9 && cam->fov > 0.1) + (cam->fov >= 179.9) * 179.9
		+ (cam->fov <= 0.1) * 0.1;
	return (1);
}

int	parse_cam(t_data *data, char *line, unsigned short *current_idx)
{
	char	**split[3];

	(void)current_idx;
	split[0] = ft_split(line, ' ');
	if (!split[0] || !split[0][1] || !split[0][2] || !split[0][3]
		|| split[0][4] != NULL)
		return (free_split(split[0]), 0);
	split[1] = ft_split(split[0][1], ',');
	split[2] = ft_split(split[0][2], ',');
	if (!validate_coords(split[1]) || !validate_coords(split[2]))
		return (free_split(split[0]), free_split(split[1]),
			free_split(split[2]), 0);
	if (!validate_camera_data(split, &data->scene.camera))
		return (free_split(split[0]), free_split(split[1]),
			free_split(split[2]), 0);
	free_split(split[1]);
	free_split(split[2]);
	free_split(split[0]);
	return (1);
}

static void	init_parser_array(t_parser *array)
{
	array[0] = (t_parser){"sp ", 3, parse_sp};
	array[1] = (t_parser){"pl ", 3, parse_pl};
	array[2] = (t_parser){"cy ", 3, parse_cy};
	array[3] = (t_parser){"C ", 2, parse_cam};
	array[4] = (t_parser){"A ", 2, parse_ambient};
	array[5] = (t_parser){"L ", 2, parse_lightsrc};
	array[6] = (t_parser){NULL, 0, NULL};
}

static int	parse_line(t_data *data, char *line, unsigned short *current,
	t_parser *array)
{
	long long	i;

	if (is_empty_line(line))
		return (1);
	i = -1;
	while (array[++i].type)
		if (ft_strncmp(line, array[i].type, array[i].len) == 0)
			return (array[i].func(data, line, current));
	return (0);
}

static bool	parse_objects(t_data *data, int fd)
{
	t_parser		array[7];
	char			*line;
	unsigned short	current;

	init_parser_array(array);
	current = 0;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		if (!parse_line(data, line, &current, array))
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	line = get_next_line(fd, -1);
	if (line)
		free(line);
	if (current != data->scene.num_objects)
		return (false);
	return (true);
}

bool	parse(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	if (!permissible_count(data, fd))
		return (close(fd), false);
	close(fd);
	if (data->scene.num_objects == 0)
		return (false);
	data->scene.all_objects = malloc(sizeof(t_object)
			* data->scene.num_objects);
	if (!data->scene.all_objects)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(data->scene.all_objects), false);
	if (!parse_objects(data, fd))
		return (close(fd), free(data->scene.all_objects), false);
	close(fd);
	return (true);
}
