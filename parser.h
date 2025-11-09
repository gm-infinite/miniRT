/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/11/02 14:10:43 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include <stdbool.h>

typedef struct s_parse
{
	t_data					*data;
	unsigned short			obj_idx;
	char					**tokens;
	short					fd;
	int						line_num;
}	t_parse;

typedef bool				(*t_validate_func)(const char *str, void *out);

typedef struct s_validator
{
	t_validate_func			func;
	void					*output;
}	t_validator;

typedef bool				(*t_parse_func)(t_parse *ctx);

typedef struct s_parse_def
{
	const char				*id;
	t_parse_func			func;
	bool					is_unique;
	int						token_count;
}	t_parse_def;

bool						parse(t_data *data, char *filename);

/* Element parsers */
bool						parse_ambient(t_parse *ctx);
bool						parse_camera(t_parse *ctx);
bool						parse_light(t_parse *ctx);
bool						parse_sphere(t_parse *ctx);
bool						parse_plane(t_parse *ctx);
bool						parse_cylinder(t_parse *ctx);

/* Validation functions */
bool						validate_double(const char *str, void *out);
bool						validate_vector(const char *str, void *out);
bool						validate_color(const char *str, void *out);
bool						validate_normal(const char *str, void *out);
bool						validate_ratio(const char *str, void *out);
bool						validate_fov(const char *str, void *out);
bool						validate_positive(const char *str, void *out);

/* Parser utils */
double						ft_atof(const char *str);
char						**tokenize_line(char *line);
void						free_tokens(char **tokens);
bool						check_token_count(char **tokens, int expected);

/* File utils */
bool						count_elements(char *filename, t_data *data);
char						*get_next_line(int fd, int eof);

/* Parser table */
const t_parse_def			*get_parse_table(void);

#endif