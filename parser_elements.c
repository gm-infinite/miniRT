/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:13:21 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 15:38:27 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_ambient(t_parse *ctx)
{
	t_ambient_light	*amb;
	t_validator		validators[2];

	amb = &ctx->data->scene.ambient_light;
	validators[0] = (t_validator){validate_ratio, &amb->intensity};
	validators[1] = (t_validator){validate_color, &amb->color};
	if (!validators[0].func(ctx->tokens[1], validators[0].output))
		return (false);
	if (!validators[1].func(ctx->tokens[2], validators[1].output))
		return (false);
	return (true);
}

bool	parse_camera(t_parse *ctx)
{
	t_camera	*cam;

	cam = &ctx->data->scene.camera;
	if (!validate_vector(ctx->tokens[1], &cam->origin))
		return (false);
	if (!validate_normal(ctx->tokens[2], &cam->direction))
		return (false);
	if (!validate_fov(ctx->tokens[3], &cam->fov))
		return (false);
	return (true);
}

bool	parse_light(t_parse *ctx)
{
	t_light	*light;

	light = &ctx->data->scene.light;
	if (!validate_vector(ctx->tokens[1], &light->position))
		return (false);
	if (!validate_ratio(ctx->tokens[2], &light->intensity))
		return (false);
	return (true);
}

bool	parse_sphere(t_parse *ctx)
{
	t_sphere	*sp;
	t_object	*obj;
	double		diameter;

	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	sp = &obj->object.sphere;
	obj->type = SPHERE;
	if (!validate_vector(ctx->tokens[1], &sp->origin))
		return (false);
	if (!validate_positive(ctx->tokens[2], &diameter))
		return (false);
	sp->radius = diameter / 2.0;
	if (!validate_color(ctx->tokens[3], &sp->color))
		return (false);
	ctx->obj_idx++;
	return (true);
}

bool	parse_plane(t_parse *ctx)
{
	t_plane		*pl;
	t_object	*obj;

	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	pl = &obj->object.plane;
	obj->type = PLANE;
	if (!validate_vector(ctx->tokens[1], &pl->origin))
		return (false);
	if (!validate_normal(ctx->tokens[2], &pl->direction))
		return (false);
	if (!validate_color(ctx->tokens[3], &pl->color))
		return (false);
	ctx->obj_idx++;
	return (true);
}
