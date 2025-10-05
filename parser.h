/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:42:00 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include <stdbool.h>

/* Parser context - avoids globals */
typedef struct s_parse
{
	t_data					*data;
	unsigned short			obj_idx;
	char					**tokens;
	short					fd;
	int						line_num;
}	t_parse;

/* Validator function type */
typedef bool				(*t_validate_func)(const char *str, void *out);

/* Validator for parsing with validation */
typedef struct s_validator
{
	t_validate_func			func;
	void					*output;
}	t_validator;

/* Generic parser function type */
typedef bool				(*t_parse_func)(t_parse *ctx);

/* Parser entry for dispatch table */
typedef struct s_parse_def
{
	const char				*id;
	t_parse_func			func;
	bool					is_unique;
	int						token_count;
}	t_parse_def;

/* Main parsing functions */
bool						parse(t_data *data, char *filename);
bool						parse_file(int fd, t_data *data);

/* Element parsers - simplified signatures */
bool						parse_ambient(t_parse *ctx);
bool						parse_camera(t_parse *ctx);
bool						parse_light(t_parse *ctx);
bool						parse_sphere(t_parse *ctx);
bool						parse_plane(t_parse *ctx);
bool						parse_cylinder(t_parse *ctx);

/* Validation functions - now return bool and set output via pointer */
bool						validate_double(const char *str, void *out);
bool						validate_vector(const char *str, void *out);
bool						validate_color(const char *str, void *out);
bool						validate_normal(const char *str, void *out);
bool						validate_ratio(const char *str, void *out);
bool						validate_fov(const char *str, void *out);
bool						validate_positive(const char *str, void *out);

/* Parser utilities */
double						ft_atof(const char *str);
char						**tokenize_line(char *line);
void						free_tokens(char **tokens);
int							count_tokens(char **tokens);
bool						dispatch_element(char **tokens, t_parse *ctx);
bool						check_token_count(char **tokens, int expected);

/* File utilities */
bool						count_elements(char *filename, t_data *data);
char						*get_next_line(int fd, int eof);

/* Parser table access */
const t_parse_def			*get_parse_table(void);

#endif