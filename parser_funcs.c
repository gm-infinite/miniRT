/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:02:40 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/05 19:33:00 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_sp(t_data *data, char *line, unsigned short current)
{
    // sp 0.0,0.0,20.6 12.6 10,0,255
    // x, y, z coordinates of the sphere center: 0.0,0.0,20.6
    // the sphere diameter: 12.6
    // R,G,B colors in the range [0-255]: 10, 0, 255
	t_sphere temp_sphere;
	char	**space_split;
	char	***comma_split;
	
	// DO NOT FORGET TO FREE THESE !!!!!
	space_split = ft_split(line, ' ');
	if (!space_split || !(space_split[3]))
		return ;
	short i = 0;
	while (space_split[++i] != NULL)
		comma_split[i] = ft_split(space_split[i], ',');
	
	temp_sphere.origin = vector(ft_atof(comma_split[1][0]), ft_atof(comma_split[1][1]), ft_atof(comma_split[1][2]));
	// we're given the diameter, not radius. we might need to float-divide by two. 
	temp_sphere.radius = ft_atof(space_split[2]);
	
	temp_sphere.color = (t_color){ft_atoi(comma_split[3][0]), ft_atoi(comma_split[3][1]), ft_atoi(comma_split[3][2])};
    data->scene.all_objects[current].type = SPHERE;
	data->scene.all_objects[current].object.sphere = temp_sphere;
}

void	parse_pl(t_data *data, char *line, unsigned short current)
{
    // pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
    // x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
    // 3D normalized normal vector, in the range [-1,1] for each x, y, z axis: 0.0,1.0,0.0
    // R,G,B colors in the range [0-255]: 0,0,225
	t_plane temp_plane;
	char	**space_split;
	char	***comma_split;
	
	// DO NOT FORGET TO FREE THESE !!!!!
	space_split = ft_split(line, ' ');
	if (!space_split || !(space_split[3]))
		return ;
	short i = 0;
	while (space_split[++i] != NULL)
		comma_split[i] = ft_split(space_split[i], ',');
	temp_plane.direction = vector_normalize(vector(ft_atof(comma_split[2][0]), ft_atof(comma_split[2][1]), ft_atof(comma_split[2][2])));
	temp_plane.origin = vector(ft_atof(comma_split[1][0]), ft_atof(comma_split[1][1]), ft_atof(comma_split[1][2]));
	temp_plane.color = (t_color){ft_atoi(comma_split[3][0]), ft_atoi(comma_split[3][1]), ft_atoi(comma_split[3][2])};
    data->scene.all_objects[current].type = PLANE;
	data->scene.all_objects[current].object.plane = temp_plane;
}

void	parse_cy(t_data *data, char *line, unsigned short current)
{
    // cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
    // x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
    // 3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0
    // the cylinder diameter: 14.2
    // the cylinder height: 21.42
    // R, G, B colors in the range [0,255]: 10, 0, 255
	t_cylinder temp_cylinder;
	char	**space_split;
	char	***comma_split;
	
	// DO NOT FORGET TO FREE THESE !!!!!
	space_split = ft_split(line, ' ');
	if (!space_split || !(space_split[5]))
		return ;
	short i = 0;
	while (space_split[++i] != NULL)
		comma_split[i] = ft_split(space_split[i], ',');
	temp_cylinder.color = (t_color){ft_atoi(comma_split[5][0]), ft_atoi(comma_split[5][1]), ft_atoi(comma_split[5][2])};
	temp_cylinder.direction = vector_normalize(vector(ft_atof(comma_split[2][0]), ft_atof(comma_split[2][1]), ft_atof(comma_split[2][2])));
	temp_cylinder.origin = vector(ft_atof(comma_split[1][0]), ft_atof(comma_split[1][1]), ft_atof(comma_split[1][2]));
	temp_cylinder.radius = ft_atof(space_split[3]);
	temp_cylinder.h = ft_atof(space_split[4][0]);
	transform_matrix_cy(&temp_cylinder);
    data->scene.all_objects[current].type = CYLINDER;
	data->scene.all_objects[current].object.cylinder = temp_cylinder;
}

/* void    parse_lightsrc(t_data *data, char *line)
{
    
} */
// STILL NO BOUND CHECKS! be careful
void    parse_ambient(t_data *data, char *line)
{
    // A 0.2 255,255,255
    // ambient lighting ratio in the range [0.0,1.0]: 0.2
    // R, G, B colors in the range [0-255]: 255, 255, 255
    char	**space_split;
	char	**comma_split;

	space_split = ft_split(line, ' ');
	if (!space_split)
		return ;
	comma_split = ft_split(space_split[2], ',');
	if (!comma_split)
		return ;
    data->scene.ambient_light.intensity = ft_atof(space_split[1]);
    data->scene.ambient_light.color = (t_color){
        ft_atoi(comma_split[0]),
        ft_atoi(comma_split[1]),
        ft_atoi(comma_split[2])
    };
	free_split(space_split);
	free_split(comma_split);
}
