/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:12:16 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 16:35:08 by kuzyilma         ###   ########.fr       */
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
	double		matrix[3][3];
	double		inverse_matrix[3][3];
}	t_camera;

void		transform_matrix_c(t_camera *cam);
t_vector	vector_transform_camera(t_vector vec, t_camera *cam);
t_point		point_transform_camera(t_point point, t_camera *cam);

#endif
