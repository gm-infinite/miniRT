/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:32:04 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:50:29 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

const t_parse_def	*get_parse_table(void)
{
	static const t_parse_def	g_parse_table[] = {
	{"A", parse_ambient, true, 3},
	{"C", parse_camera, true, 4},
	{"L", parse_light, true, 4},
	{"sp", parse_sphere, false, 4},
	{"pl", parse_plane, false, 4},
	{"cy", parse_cylinder, false, 6},
	{NULL, NULL, false, 0}
	};

	return (g_parse_table);
}

bool	dispatch_element(char **tokens, t_parse *ctx)
{
	const t_parse_def	*entry;
	int					i;

	if (!tokens || !tokens[0])
		return (true);
	entry = get_parse_table();
	i = -1;
	while (entry[++i].id)
	{
		if (ft_strlen(tokens[0]) == ft_strlen(entry[i].id)
			&& ft_strncmp(tokens[0], entry[i].id,
				ft_strlen(entry[i].id)) == 0)
		{
			ctx->tokens = tokens;
			if (!check_token_count(tokens, entry[i].token_count))
				return (false);
			return (entry[i].func(ctx));
		}
	}
	return (false);
}

static bool	process_line(char *line, t_parse *ctx)
{
	char	**tokens;
	bool	result;

	if (!line || !*line || *line == '\n')
		return (true);
	tokens = tokenize_line(line);
	if (!tokens)
		return (false);
	result = dispatch_element(tokens, ctx);
	free_tokens(tokens);
	return (result);
}

bool	parse_file(int fd, t_data *data)
{
	t_parse	ctx;
	char	*line;
	bool	success;

	ctx.data = data;
	ctx.obj_idx = 0;
	ctx.fd = fd;
	ctx.line_num = 0;
	success = true;
	line = get_next_line(fd, 0);
	while (line && success)
	{
		ctx.line_num++;
		success = process_line(line, &ctx);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, -1);
	if (line)
		free(line);
	return (success && ctx.obj_idx == data->scene.num_objects);
}

bool	parse(t_data *data, char *filename)
{
	int	fd;

	if (!count_elements(filename, data))
		return (false);
	if (data->scene.num_objects > 0)
	{
		data->scene.all_objects = malloc(sizeof(t_object)
				* data->scene.num_objects);
		if (!data->scene.all_objects)
			return (false);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (data->scene.all_objects)
			free(data->scene.all_objects);
		return (false);
	}
	if (!parse_file(fd, data))
	{
		close(fd);
		return (free(data->scene.all_objects), false);
	}
	return (close(fd), true);
}
