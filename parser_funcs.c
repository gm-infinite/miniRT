/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:02:40 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 14:37:52 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <math.h>

bool	parse_sphere(t_parse_ctx *ctx)
{
	t_sphere	*sp;
	t_object	*obj;
	double		diameter;

	if (count_tokens(ctx->tokens) != 4)
		return (false);
	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	sp = &obj->object.sphere;
	obj->type = SPHERE;
	if (!parse_vector(ctx->tokens[1], &sp->origin))
		return (false);
	if (!parse_double(ctx->tokens[2], &diameter))
		return (false);
	if (diameter <= 0.0)
		return (false);
	sp->radius = diameter / 2.0;
	if (!parse_color(ctx->tokens[3], &sp->color))
		return (false);
	ctx->obj_idx++;
	return (true);
}

bool	parse_plane(t_parse_ctx *ctx)
{
	t_plane		*pl;
	t_object	*obj;
	t_vector	normal;

	if (count_tokens(ctx->tokens) != 4)
		return (false);
	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	pl = &obj->object.plane;
	obj->type = PLANE;
	if (!parse_vector(ctx->tokens[1], &pl->origin))
		return (false);
	if (!parse_vector(ctx->tokens[2], &normal))
		return (false);
	if (!validate_normalized(normal.x, normal.y, normal.z))
		return (false);
	pl->direction = v3_norm(normal);
	if (!parse_color(ctx->tokens[3], &pl->color))
		return (false);
	ctx->obj_idx++;
	return (true);
}

static bool	parse_cylinder_params(t_cylinder *cy, char **tokens)
{
	t_vector	axis;
	double		diameter;

	if (!parse_vector(tokens[1], &cy->origin))
		return (false);
	if (!parse_vector(tokens[2], &axis))
		return (false);
	if (!validate_normalized(axis.x, axis.y, axis.z))
		return (false);
	cy->direction = v3_norm(axis);
	if (!parse_double(tokens[3], &diameter))
		return (false);
	if (diameter <= 0.0)
		return (false);
	cy->radius = diameter / 2.0;
	if (!parse_double(tokens[4], &cy->h))
		return (false);
	if (cy->h <= 0.0)
		return (false);
	if (!parse_color(tokens[5], &cy->color))
		return (false);
	transform_matrix_cy(cy);
	return (true);
}

bool	parse_cylinder(t_parse_ctx *ctx)
{
	t_cylinder	*cy;
	t_object	*obj;

	if (count_tokens(ctx->tokens) != 6)
		return (false);
	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	cy = &obj->object.cylinder;
	obj->type = CYLINDER;
	if (!parse_cylinder_params(cy, ctx->tokens))
		return (false);
	ctx->obj_idx++;
	return (true);
}
