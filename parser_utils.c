/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:07:57 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/04 23:23:33 by emgenc           ###   ########.fr       */
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
		exponent = exponent * 10 + (**str - '0');
		(*str)++;
	}
	result = 1.0;
	while (exponent-- > 0)
		result *= (exp_sign == 1) ? 10.0 : 0.1;
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

void	free_split(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
