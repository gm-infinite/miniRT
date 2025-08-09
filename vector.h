/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:15:00 by kuzyilma          #+#    #+#             */
/*   Updated: 2025/08/09 17:51:00 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "coordinates_3d.h"

typedef t_coordinates_3d	t_vector;

t_vector	vector_add(t_vector v, t_vector u);
t_vector	vector_negate(t_vector v);
t_vector	vector_constant_multipy(double a, t_vector v);
t_vector	vector_constant_divide(double a, t_vector v);
double		vector_length(t_vector v);

t_vector	vector_normilize(t_vector v);
double		vector_dot_product(t_vector v1, t_vector v2);
t_vector	vector_cross_product(t_vector v1, t_vector v2);

#endif