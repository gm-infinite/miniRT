/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:12:16 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 13:47:21 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "objects.h"

typedef struct s_camera
{
	t_point		origin;
	t_vector	direction;
	double		fov;
	/* double		matrix[3][3]; */
}	t_camera;

#endif
