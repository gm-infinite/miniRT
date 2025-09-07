/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/07 16:17:01 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	permissible_count(t_data *data, int fd)
{
	unsigned long long	cal[3];
	char				*line;

	cal[0] = 0;
	cal[1] = 0;
	cal[2] = 0;
	line = get_next_line(fd, 0);
	data->scene.num_objects = 0;
	while (line != NULL)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			cal[0]++;
		else if (ft_strncmp(line, "A ", 2) == 0)
			cal[1]++;
		else if (ft_strncmp(line, "L ", 2) == 0)
			cal[2]++;
		else if (ft_strncmp(line, "sp ", 3) == 0 || ft_strncmp(line, "pl ", 3) == 0 || ft_strncmp(line, "cy ", 3) == 0)
			data->scene.num_objects++;
		free(line);
		line = get_next_line(fd, 0);
	}
	line = get_next_line(fd, -1);
	if (cal[0] != 1 || cal[1] + cal[2] == 0 || (cal[1] > 1 || cal[2] > 1))
	{
		if (line)
			free(line);
		return (false);
	}
	if (line)
		free(line);
	return (true);
}

void    parse_cam(t_data *data, char *line, unsigned short *current_idx)
{
	char	**space_split;
	char	**pos;
	char	**dir;

	(void)current_idx;
	space_split = ft_split(line, ' ');
	if (!space_split || !space_split[1] || !space_split[2] || !space_split[3])
		return ;
	pos = ft_split(space_split[1], ',');
	dir = ft_split(space_split[2], ',');
	if (!pos || !dir || !pos[0] || !pos[1] || !pos[2]
		|| !dir[0] || !dir[1] || !dir[2])
	{
		free_split(space_split);
		free_split(pos);
		free_split(dir);
		return ;
	}
	data->scene.camera = (t_camera){
		vector(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2])),
		vector_normalize(vector(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2]))),
		ft_atof(space_split[3])
	};
	free_split(pos);
	free_split(dir);
	free_split(space_split);
}

bool	parse(t_data *data, int fd)
{
	char		*line;
	t_parser	array[] = {{"sp ", 3, parse_sp}, {"pl ", 3, parse_pl},
	{"cy ", 3, parse_cy}, {"C ", 2, parse_cam}, {"A ", 2, parse_ambient},
	{"L ", 2, parse_lightsrc}, {NULL, 0, NULL}};
	long long		i;
	unsigned short	current;

	if (!permissible_count(data, fd))
		return (false);
	// rewind file since permissible_count consumed it
	lseek(fd, 0, SEEK_SET);
	data->scene.all_objects = malloc(sizeof(t_object_list) * data->scene.num_objects);
	if (!(data->scene.num_objects) || data->scene.num_objects == 0)
		return (false);
	line = get_next_line(fd, 0);
	current = 0;
	while (line != NULL)
	{
		i = -1;
		while (array[++i].type)
		{
			if (ft_strncmp(line, array[i].type, array[i].len) == 0)
			{
				array[i].func(data, line, &current);
				break ;
			}
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	line = get_next_line(fd, -1);
	if (line)
		free(line);
	return (true);
}
