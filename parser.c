/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/05 20:29:28 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	permissible_count(int fd)
{
	unsigned long long	cal[3];
	char				*line;

	cal[0] = 0;
	cal[1] = 0;
	cal[2] = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			cal[0]++;
		else if (ft_strncmp(line, "A ", 2) == 0)
			cal[1]++;
		else if (ft_strncmp(line, "L ", 2) == 0)
			cal[2]++;
		free(line);
		line = get_next_line(fd);
	}
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

void    parse_cam(t_data *data, char *line)
{
	char	**space_split;
	char	***comma_split;
	
	// DO NOT FORGET TO FREE THESE !!!!!
	space_split = ft_split(line, ' ');
	if (!space_split || !(space_split[3]))
		return ;
	short i = 0;
	while (space_split[++i] != NULL)
		comma_split[i] = ft_split(space_split[i], ',');
	data->scene.camera = (t_camera){vector(ft_atof(comma_split[1][0]), ft_atof(comma_split[1][1]), ft_atof(comma_split[1][2])), vector_normalize(vector(ft_atof(comma_split[2][0]), ft_atof(comma_split[2][1]), ft_atof(comma_split[2][2]))), ft_atof(space_split[3])};
}

bool	parse(t_data *data, int fd)
{
	char		*line;
	t_parser	array[7];
	long long	i;

	if (!permissible_count(fd))
		return (false);
	array = (t_parser[7]){{"sp ", 3, parse_sp}, {"pl ", 3, parse_pl},
	{"cy ", 3, parse_cy}, {"C ", 2, parse_cam}, {"A ", 2, parse_ambient},
	{"L ", 2, parse_lightsrc}, {NULL, 0, NULL}};
	line = get_next_line(fd);
	while (line)
	{
		i = -1;
		while (array[++i].type)
		{
			if (ft_strncmp(line, array[i].type, array[i].len) == 0)
			{
				array[i].func(data, line, i);
				if (ft_strncmp(array[i].type, "sp", 2) == 0 || ft_strncmp(array[i].type, "pl", 2) == 0 || ft_strncmp(array[i].type, "cy", 2) == 0)
					data->scene.num_objects++;
				break ;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (true);
}
