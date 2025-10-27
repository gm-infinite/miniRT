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
	transform_matrix_c(cam);
	ctx->camera_parsed = true;
	return (true);
}

bool	parse_light(t_parse *ctx)
{
	t_light	*light;
	t_point	world_pos;

	light = &ctx->data->scene.light;
	if (!validate_vector(ctx->tokens[1], &world_pos))
		return (false);
	if (!validate_ratio(ctx->tokens[2], &light->intensity))
		return (false);
	if (ctx->camera_parsed)
		light->position = point_transform_camera(world_pos,
				&ctx->data->scene.camera);
	else
		light->position = world_pos;
	return (true);
}

bool	parse_sphere(t_parse *ctx)
{
	t_sphere	*sp;
	t_object	*obj;
	double		diameter;
	t_point		world_origin;

	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	sp = &obj->object.sphere;
	obj->type = SPHERE;
	if (!validate_vector(ctx->tokens[1], &world_origin))
		return (false);
	if (!validate_positive(ctx->tokens[2], &diameter))
		return (false);
	sp->radius = diameter / 2.0;
	if (!validate_color(ctx->tokens[3], &sp->color))
		return (false);
	if (ctx->camera_parsed)
		sp->origin = point_transform_camera(world_origin,
				&ctx->data->scene.camera);
	else
		sp->origin = world_origin;
	ctx->obj_idx++;
	return (true);
}

bool	parse_plane(t_parse *ctx)
{
	t_plane		*pl;
	t_object	*obj;
	t_point		world_origin;
	t_vector	world_direction;

	obj = &ctx->data->scene.all_objects[ctx->obj_idx];
	pl = &obj->object.plane;
	obj->type = PLANE;
	if (!validate_vector(ctx->tokens[1], &world_origin))
		return (false);
	if (!validate_normal(ctx->tokens[2], &world_direction))
		return (false);
	if (!validate_color(ctx->tokens[3], &pl->color))
		return (false);
	if (ctx->camera_parsed)
	{
		pl->origin = point_transform_camera(world_origin,
				&ctx->data->scene.camera);
		pl->direction = vector_transform_camera(world_direction,
				&ctx->data->scene.camera);
	}
	else
	{
		pl->origin = world_origin;
		pl->direction = world_direction;
	}
	ctx->obj_idx++;
	return (true);
}
