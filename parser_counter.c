/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:17:10 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:17:12 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

static bool	validate_element(char **tokens, int *unique_counts, t_data *data)
{
	const t_parse_def	*entry;
	int					i;

	entry = get_parse_table();
	i = 0;
	while (entry[i].id)
	{
		if (ft_strlen(tokens[0]) == ft_strlen(entry[i].id)
			&& ft_strncmp(tokens[0], entry[i].id,
				ft_strlen(entry[i].id)) == 0)
		{
			if (entry[i].is_unique)
			{
				if (unique_counts[i]++ > 0)
					return (false);
			}
			else
				data->scene.num_objects++;
			return (check_token_count(tokens, entry[i].token_count));
		}
		i++;
	}
	return (false);
}

static bool	process_count_line(char *line, int *unique_counts, t_data *data)
{
	char	**tokens;
	bool	valid;

	if (!line || !*line || *line == '\n')
		return (true);
	tokens = tokenize_line(line);
	if (!tokens)
		return (false);
	valid = validate_element(tokens, unique_counts, data);
	free_tokens(tokens);
	return (valid);
}

bool	count_elements(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		unique_counts[3];
	bool	valid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	ft_bzero(unique_counts, sizeof(unique_counts));
	data->scene.num_objects = 0;
	valid = true;
	line = get_next_line(fd, 0);
	while (line && valid)
	{
		valid = process_count_line(line, unique_counts, data);
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, -1);
	if (line)
		free(line);
	close(fd);
	return (valid && unique_counts[0] == 1
		&& unique_counts[1] == 1 && unique_counts[2] == 1);
}
