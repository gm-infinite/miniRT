/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 11:37:42 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/30 13:50:51 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "objects.h"

void	transform_matrix_c(t_camera *cam)
{
    t_vector	new_x;
    t_vector	new_y;
    t_vector	new_z;
    t_vector	temp;

    new_x = v3_norm(cam->direction);
    if (fabs(new_x.x) < 0.99)
        temp = vector(1, 0, 0);
    else
        temp = vector(0, 1, 0);
    new_y = v3_norm(v3_cross(temp, new_x));
    new_z = v3_cross(new_x, new_y);
    cam->matrix[0][0] = new_x.x;
    cam->matrix[0][1] = new_x.y;
    cam->matrix[0][2] = new_x.z;
    cam->matrix[1][0] = new_y.x;
    cam->matrix[1][1] = new_y.y;
    cam->matrix[1][2] = new_y.z;
    cam->matrix[2][0] = new_z.x;
    cam->matrix[2][1] = new_z.y;
    cam->matrix[2][2] = new_z.z;
}
