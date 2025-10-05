/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 13:53:22 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include <stdbool.h>

typedef int	(*t_parser_function)(t_data *data, char *line,
				unsigned short *current_idx);

typedef struct s_parser
{
	char				*type;
	int					len;
	t_parser_function	func;
}	t_parser;

char	*get_next_line(int fd, int eof);
int		parse_sp(t_data *data, char *line, unsigned short *current_idx);
int		parse_pl(t_data *data, char *line, unsigned short *current_idx);
int		parse_cy(t_data *data, char *line, unsigned short *current_idx);
int		parse_cam(t_data *data, char *line, unsigned short *current_idx);
int		parse_lightsrc(t_data *data, char *line, unsigned short *current_idx);
int		parse_ambient(t_data *data, char *line, unsigned short *current_idx);
double	ft_atof(const char *str);
void	free_split(char **arr);
bool	parse(t_data *data, char *filename);
int		validate_normalized(double x, double y, double z);
int		validate_coords(char **coords);

#endif
