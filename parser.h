/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 23:30:03 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/05 20:29:09 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "rt.h"
# include "e-gnl/get_next_line.h"

typedef void (*t_parser_function)(t_data *data, char *line, unsigned short c);

void	parse_sp(t_data *data, char *line, unsigned short current);
void	parse_pl(t_data *data, char *line, unsigned short current);
void	parse_cy(t_data *data, char *line, unsigned short current);
void    parse_ambient(t_data *data, char *line);

typedef struct s_parser
{
    char				*type;
    int					len;
    t_parser_function	func;
}	t_parser;

#endif