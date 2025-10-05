/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:15:00 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/10/05 14:43:03 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "coordinates_3d.h"

typedef t_coordinates_3d	t_vector;

t_vector	v3_add(t_vector v, t_vector u);
t_vector	v3_sub(t_vector v1, t_vector v2);
t_vector	v3_mult(double a, t_vector v);
t_vector	v3_const_div(double a, t_vector v);
double		v3_len(t_vector v);

t_vector	v3_norm(t_vector v);
double		v3_dot(t_vector v1, t_vector v2);
t_vector	v3_cross(t_vector v1, t_vector v2);
t_vector	vector(double x, double y, double z);
t_vector	v3_neg(t_vector v);

#endif
