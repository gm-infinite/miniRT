/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:00:43 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <math.h>

static t_parse_entry	*get_parse_table(void)
{
	static t_parse_entry	table[7];
	static bool				initialized = false;

	if (!initialized)
	{
		table[0] = (t_parse_entry){"A", parse_ambient, true};
		table[1] = (t_parse_entry){"C", parse_camera, true};
		table[2] = (t_parse_entry){"L", parse_light, true};
		table[3] = (t_parse_entry){"sp", parse_sphere, false};
		table[4] = (t_parse_entry){"pl", parse_plane, false};
		table[5] = (t_parse_entry){"cy", parse_cylinder, false};
		table[6] = (t_parse_entry){NULL, NULL, false};
		initialized = true;
	}
	return (table);
}

static bool	dispatch_parse(char *line, t_parse_ctx *ctx)
{
	int				i;
	char			**tokens;
	t_parse_entry	*table;

	if (!line || !*line || *line == '\n')
		return (true);
	tokens = tokenize_line(line);
	if (!tokens)
		return (false);
	ctx->tokens = tokens;
	table = get_parse_table();
	i = -1;
	while (table[++i].id)
	{
		if (ft_strlen(tokens[0]) == ft_strlen(table[i].id)
			&& ft_strncmp(tokens[0], table[i].id,
				ft_strlen(table[i].id)) == 0)
		{
			if (!table[i].func(ctx))
				return (free_tokens(tokens), false);
			free_tokens(tokens);
			return (true);
		}
	}
	free_tokens(tokens);
	return (false);
}

bool	parse_file(int fd, t_data *data)
{
	t_parse_ctx	ctx;
	char		*line;
	bool		success;

	ctx.data = data;
	ctx.obj_idx = 0;
	success = true;
	line = get_next_line(fd, 0);
	while (line && success)
	{
		success = dispatch_parse(line, &ctx);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, -1);
	if (line)
		free(line);
	return (success && ctx.obj_idx == data->scene.num_objects);
}

static bool	validate_and_count(char *line, int *counts, t_data *data)
{
	int				i;
	t_parse_entry	*table;
	char			**tokens;

	if (!line || !*line || *line == '\n')
		return (true);
	tokens = tokenize_line(line);
	if (!tokens)
		return (false);
	table = get_parse_table();
	i = -1;
	while (table[++i].id)
	{
		if (ft_strlen(tokens[0]) == ft_strlen(table[i].id)
			&& ft_strncmp(tokens[0], table[i].id,
				ft_strlen(table[i].id)) == 0)
		{
			if (table[i].is_unique)
			{
				if (counts[i]++ > 0)
					return (free_tokens(tokens), false);
			}
			else
				data->scene.num_objects++;
			return (free_tokens(tokens), true);
		}
	}
	return (free_tokens(tokens), false);
}

bool	count_elements(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		counts[3];
	bool	valid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	ft_bzero(counts, sizeof(counts));
	data->scene.num_objects = 0;
	valid = true;
	line = get_next_line(fd, 0);
	while (line && valid)
	{
		valid = validate_and_count(line, counts, data);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, -1);
	if (line)
		free(line);
	close(fd);
	return (valid && counts[0] == 1 && counts[1] == 1 && counts[2] == 1);
}

bool	parse(t_data *data, char *filename)
{
	int	fd;

	if (!count_elements(filename, data))
		return (false);
	if (data->scene.num_objects == 0)
		return (false);
	data->scene.all_objects = malloc(sizeof(t_object)
			* data->scene.num_objects);
	if (!data->scene.all_objects)
		return (false);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(data->scene.all_objects), false);
	if (!parse_file(fd, data))
		return (close(fd), free(data->scene.all_objects), false);
	close(fd);
	return (true);
}
