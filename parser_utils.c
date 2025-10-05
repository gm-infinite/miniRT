/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:13:16 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 14:40:33 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "parser.h"

static const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
		str++;
	return (str);
}

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static double	parse_integer_part(const char **str, int *has_digits)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
		*has_digits = 1;
	}
	return (result);
}

static double	parse_fractional_part(const char **str, int *has_digits)
{
	double	result;
	double	divisor;

	result = 0.0;
	divisor = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result = result + (**str - '0') / divisor;
			divisor *= 10.0;
			(*str)++;
			*has_digits = 1;
		}
	}
	return (result);
}

static double	parse_exponent(const char **str)
{
	int		exp_sign;
	int		exponent;
	double	result;

	if (**str != 'e' && **str != 'E')
		return (1.0);
	(*str)++;
	exp_sign = 1;
	if (**str == '-')
	{
		exp_sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	exponent = 0;
	while (**str >= '0' && **str <= '9')
	{
		exponent *= 10 + (**str - '0');
		(*str)++;
	}
	result = 1.0;
	while (exponent-- > 0)
		result *= pow(10.0, exp_sign);
	return (result);
}

double	ft_atof(const char *str)
{
	int			sign;
	double		result;
	int			has_digits;
	const char	*start;

	if (!str || !str[0])
		return (NAN);
	str = skip_whitespace(str);
	start = str;
	sign = parse_sign(&str);
	has_digits = 0;
	result = parse_integer_part(&str, &has_digits);
	result += parse_fractional_part(&str, &has_digits);
	if (!has_digits)
		return (NAN);
	result *= parse_exponent(&str);
	str = skip_whitespace(str);
	if (*str != '\0')
		return (NAN);
	if (!isfinite(result))
		return (NAN);
	return (sign * result);
}

bool	parse_vector(char *str, t_vector *vec)
{
	char	**parts;
	bool	success;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), false);
	success = true;
	vec->x = ft_atof(parts[0]);
	vec->y = ft_atof(parts[1]);
	vec->z = ft_atof(parts[2]);
	if (!isfinite(vec->x) || !isfinite(vec->y) || !isfinite(vec->z))
		success = false;
	free_tokens(parts);
	return (success);
}

bool	parse_color(char *str, t_color *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (free_tokens(parts), false);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_tokens(parts);
	if (!validate_rgb(r, g, b))
		return (false);
	color->r = r;
	color->g = g;
	color->b = b;
	return (true);
}

bool	parse_double(char *str, double *value)
{
	*value = ft_atof(str);
	return (isfinite(*value));
}

char	**tokenize_line(char *line)
{
	char	*trimmed;
	char	**tokens;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (NULL);
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	return (tokens);
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

bool	validate_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

bool	validate_normalized(double x, double y, double z)
{
	double	magnitude;

	if (!isfinite(x) || !isfinite(y) || !isfinite(z))
		return (false);
	magnitude = x * x + y * y + z * z;
	return (magnitude >= 0.99 && magnitude <= 1.01);
}

bool	validate_ratio(double ratio)
{
	return (isfinite(ratio) && ratio >= 0.0 && ratio <= 1.0);
}

bool	validate_fov(double fov)
{
	return (isfinite(fov) && fov > 0.0 && fov < 180.0);
}

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

bool	parse_ambient(t_parse_ctx *ctx)
{
	t_ambient_light	*amb;

	if (count_tokens(ctx->tokens) != 3)
		return (false);
	amb = &ctx->data->scene.ambient_light;
	if (!parse_double(ctx->tokens[1], &amb->intensity))
		return (false);
	if (!validate_ratio(amb->intensity))
		return (false);
	if (!parse_color(ctx->tokens[2], &amb->color))
		return (false);
	return (true);
}

bool	parse_camera(t_parse_ctx *ctx)
{
	t_camera	*cam;
	t_vector	dir;

	if (count_tokens(ctx->tokens) != 4)
		return (false);
	cam = &ctx->data->scene.camera;
	if (!parse_vector(ctx->tokens[1], &cam->origin))
		return (false);
	if (!parse_vector(ctx->tokens[2], &dir))
		return (false);
	if (!validate_normalized(dir.x, dir.y, dir.z))
		return (false);
	cam->direction = v3_norm(dir);
	if (!parse_double(ctx->tokens[3], &cam->fov))
		return (false);
	if (!validate_fov(cam->fov))
		return (false);
	if (cam->fov < 0.1)
		cam->fov = 0.1;
	if (cam->fov > 179.9)
		cam->fov = 179.9;
	return (true);
}

bool	parse_light(t_parse_ctx *ctx)
{
	t_light	*light;

	if (count_tokens(ctx->tokens) != 4)
		return (false);
	light = &ctx->data->scene.light;
	if (!parse_vector(ctx->tokens[1], &light->position))
		return (false);
	if (!parse_double(ctx->tokens[2], &light->intensity))
		return (false);
	if (!validate_ratio(light->intensity))
		return (false);
	return (true);
}
