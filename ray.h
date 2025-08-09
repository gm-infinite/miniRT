
#ifndef RAY_H
# define RAY_H
#include "vector.h"

typedef t_coordinates_3d t_point;

typedef struct s_ray
{
	t_vector	direction;
	t_point 	origin;
}	t_ray;

typedef struct	s_plane
{
	t_vector	normal;
	t_point		origin;
}	t_plane;

#endif