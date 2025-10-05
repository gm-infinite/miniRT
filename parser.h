/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 14:37:32 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include <stdbool.h>

/* Parser context to avoid globals while passing data */
typedef struct s_parse_ctx
{
	t_data			*data;
	unsigned short	obj_idx;
	char			**tokens;
}	t_parse_ctx;

/* Generic parser function type */
typedef bool	(*t_parse_func)(t_parse_ctx *ctx);

/* Parser entry for dispatch table */
typedef struct s_parse_entry
{
	const char		*id;
	t_parse_func	func;
	bool			is_unique;
}	t_parse_entry;

/* Main parsing functions */
bool	parse(t_data *data, char *filename);
bool	parse_file(int fd, t_data *data);

/* Element parsers */
bool	parse_ambient(t_parse_ctx *ctx);
bool	parse_camera(t_parse_ctx *ctx);
bool	parse_light(t_parse_ctx *ctx);
bool	parse_sphere(t_parse_ctx *ctx);
bool	parse_plane(t_parse_ctx *ctx);
bool	parse_cylinder(t_parse_ctx *ctx);

/* Validation helpers */
bool	validate_rgb(int r, int g, int b);
bool	validate_normalized(double x, double y, double z);
bool	validate_ratio(double ratio);
bool	validate_fov(double fov);

/* Parsing helpers */
bool	parse_vector(char *str, t_vector *vec);
bool	parse_color(char *str, t_color *color);
bool	parse_double(char *str, double *value);
char	**tokenize_line(char *line);
void	free_tokens(char **tokens);
int		count_tokens(char **tokens);

/* File utilities */
bool	count_elements(char *filename, t_data *data);
char	*get_next_line(int fd, int eof);

#endif