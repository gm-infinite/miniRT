/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/04 07:34:54 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	permissible_count(t_data *data)
{
	unsigned long long	camera_count;
	unsigned long long	ambient_count;
	unsigned long long	light_count;
	char				*line;

	camera_count = 0;
	ambient_count = 0;
	light_count = 0;
	line = get_next_line();
	while (line)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			camera_count++;
		else if (ft_strncmp(line, "A ", 2) == 0)
			ambient_count++;
		else if (ft_strncmp(line, "L ", 2) == 0)
			light_count++;
		free(line);
		line = get_next_line();
	}
	if (camera_count != 1 || ambient_count + light_count == 0)
	{
		if (line)
			free(line);
		return (false);
	}
	if (ambient_count > 1 || light_count > 1)
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
	data->scene.camera = (t_camera){vector(0, 0, 0), vector_normalize(vector(1, 0, 3)), 120};
	// Initialize other camera properties here.
}

bool	parse()
{
	char		*line;
	t_parser	array[7];
	long long	i;

	if (!permissible_count(data))
		return (false);
	array = (t_parser[7]){{"sp ", 3, &parse_sp}, {"pl ", 3, &parse_pl},
	{"cy ", 3, &parse_cy}, {"C ", 2, &parse_cam}, {"A ", 2, &parse_ambient},
	{"L ", 2, &parse_light}, {NULL, 0, NULL}};
	line = get_next_line();
	while (line)
	{
		i = -1;
		while (array[++i].type)
		{
			if (ft_strncmp(line, array[i].type, array[i].len) == 0)
			{
				array[i].func(data, line);
				if (array[i].type == "sp " || array[i].type == "pl " || array[i].type == "cy ")
					data->scene.num_objects++;
				break ;
			}
		}
		free(line);
		line = get_next_line();
	}
	if (line)
		free(line);
	return (true);
}
