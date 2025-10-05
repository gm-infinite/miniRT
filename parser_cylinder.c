/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:13:42 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:38:27 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	parse_cylinder_geometry(t_cylinder *cy, char **tokens)
{
	double	diameter;

	if (!validate_vector(tokens[1], &cy->origin))
		return (false);
	if (!validate_normal(tokens[2], &cy->direction))
		return (false);
	if (!validate_positive(tokens[3], &diameter))
		return (false);
	cy->radius = diameter / 2.0;
	if (!validate_positive(tokens[4], &cy->h))
		return (false);
	if (!validate_color(tokens[5], &cy->color))
		return (false);
	return (true);
}

bool	parse_cylinder(t_parse *ctx)
{
	t_cylinder	*cy;
	t_object	*obj;

	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	cy = &obj->object.cylinder;
	obj->type = CYLINDER;
	if (!parse_cylinder_geometry(cy, ctx->tokens))
		return (false);
	transform_matrix_cy(cy);
	ctx->obj_idx++;
	return (true);
}
