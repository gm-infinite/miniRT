/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/07 16:03:09 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include <stdbool.h>

typedef void (*t_parser_function)(t_data *data, char *line, unsigned short *current_idx);

void	parse_sp(t_data *data, char *line, unsigned short *current_idx);
void	parse_pl(t_data *data, char *line, unsigned short *current_idx);
void	parse_cy(t_data *data, char *line, unsigned short *current_idx);
void	parse_cam(t_data *data, char *line, unsigned short *current_idx);
void	parse_lightsrc(t_data *data, char *line, unsigned short *current_idx);
void	parse_ambient(t_data *data, char *line, unsigned short *current_idx);

// parser utils
double	ft_atof(const char *str);
void	free_split(char **arr);

// entry
bool	parse(t_data *data, int fd);

typedef struct s_parser
{
    char				*type;
    int					len;
    t_parser_function	func;
}	t_parser;

#endif
