/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:14:06 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/16 15:16:37 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

#include "objects.h"

typedef struct s_light
{
	t_point		position;
	t_vector	intensity;
}	t_light;

typedef struct s_ambient_light
{
	t_vector	intensity;
	t_color		color;
}	t_ambient_light;


#endif
