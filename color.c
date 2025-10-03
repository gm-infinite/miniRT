/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:50:56 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 14:54:42 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

t_color	color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	result;

	result.r = r;
	result.g = g;
	result.b = b;
	return (result);
}
