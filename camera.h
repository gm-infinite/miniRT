/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:12:16 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 13:08:46 by emgenc           ###   ########.fr       */
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
