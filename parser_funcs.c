/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:02:40 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/07 13:08:58 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_sp(t_data *data, char *line)
{
    // sp 0.0,0.0,20.6 12.6 10,0,255
    // x, y, z coordinates of the sphere center: 0.0,0.0,20.6
    // the sphere diameter: 12.6
    // R,G,B colors in the range [0-255]: 10, 0, 255
	t_sphere temp_sphere;
	char	**space_split;
	char	**pos;
	char	**col;

	
	space_split = ft_split(line, ' ');
	if (!space_split || !space_split[1] || !space_split[2] || !space_split[3])
		return ;
	pos = ft_split(space_split[1], ',');
	col = ft_split(space_split[3], ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2] || !col || !col[0] || !col[1] || !col[2])
	{
		free_split(space_split);
		free_split(pos);
		free_split(col);
		return ;
	}

	temp_sphere.origin = vector(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	// Note: spec gives diameter; if needed divide by 2 outside.
	temp_sphere.radius = ft_atof(space_split[2]);
	temp_sphere.color = (t_color){ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2])};

	data->scene.all_objects[data->scene.num_objects].type = SPHERE;
	data->scene.all_objects[data->scene.num_objects].object.sphere = temp_sphere;

	free_split(pos);
	free_split(col);
	free_split(space_split);
}

void	parse_pl(t_data *data, char *line)
{
    // pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
    // x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
    // 3D normalized normal vector, in the range [-1,1] for each x, y, z axis: 0.0,1.0,0.0
    // R,G,B colors in the range [0-255]: 0,0,225
	t_plane temp_plane;
	char	**space_split;
	char	**pos;
	char	**dir;
	char	**col;

	
	space_split = ft_split(line, ' ');
	if (!space_split || !space_split[1] || !space_split[2] || !space_split[3])
		return ;
	pos = ft_split(space_split[1], ',');
	dir = ft_split(space_split[2], ',');
	col = ft_split(space_split[3], ',');
	if (!pos || !dir || !col || !pos[0] || !pos[1] || !pos[2]
		|| !dir[0] || !dir[1] || !dir[2]
		|| !col[0] || !col[1] || !col[2])
	{
		free_split(space_split);
		free_split(pos);
		free_split(dir);
		free_split(col);
		return ;
	}
	temp_plane.direction = vector_normalize(vector(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2])));
	temp_plane.origin = vector(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	temp_plane.color = (t_color){ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2])};
	data->scene.all_objects[data->scene.num_objects].type = PLANE;
	data->scene.all_objects[data->scene.num_objects].object.plane = temp_plane;

	free_split(pos);
	free_split(dir);
	free_split(col);
	free_split(space_split);
}

void	parse_cy(t_data *data, char *line)
{
    // cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
    // x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
    // 3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0
    // the cylinder diameter: 14.2
    // the cylinder height: 21.42
    // R, G, B colors in the range [0,255]: 10, 0, 255
	t_cylinder temp_cylinder;
	char	**space_split;
	char	**pos;
	char	**dir;
	char	**col;

	
	space_split = ft_split(line, ' ');
	if (!space_split || !space_split[1] || !space_split[2] || !space_split[3]
		|| !space_split[4] || !space_split[5])
		return ;
	pos = ft_split(space_split[1], ',');
	dir = ft_split(space_split[2], ',');
	col = ft_split(space_split[5], ',');
	if (!pos || !dir || !col || !pos[0] || !pos[1] || !pos[2]
		|| !dir[0] || !dir[1] || !dir[2]
		|| !col[0] || !col[1] || !col[2])
	{
		free_split(space_split);
		free_split(pos);
		free_split(dir);
		free_split(col);
		return ;
	}
	temp_cylinder.color = (t_color){ft_atoi(col[0]), ft_atoi(col[1]), ft_atoi(col[2])};
	temp_cylinder.direction = vector_normalize(vector(ft_atof(dir[0]), ft_atof(dir[1]), ft_atof(dir[2])));
	temp_cylinder.origin = vector(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
	temp_cylinder.radius = ft_atof(space_split[3]);
	temp_cylinder.h = ft_atof(space_split[4]);
	transform_matrix_cy(&temp_cylinder);
	data->scene.all_objects[data->scene.num_objects].type = CYLINDER;
	data->scene.all_objects[data->scene.num_objects].object.cylinder = temp_cylinder;

	free_split(pos);
	free_split(dir);
	free_split(col);
	free_split(space_split);
}

void	parse_lightsrc(t_data *data, char *line)
{
    // L 0.0,0.0,-10.0 0.6
    
    char	**space_split;
    char	**pos;

    space_split = ft_split(line, ' ');
    if (!space_split || !space_split[1] || !space_split[2])
        return ;
    pos = ft_split(space_split[1], ',');
    if (!pos || !pos[0] || !pos[1] || !pos[2])
    {
        free_split(space_split);
        free_split(pos);
        return ;
    }
    data->scene.light.position = vector(ft_atof(pos[0]), ft_atof(pos[1]), ft_atof(pos[2]));
    data->scene.light.intensity = ft_atof(space_split[2]);
    free_split(pos);
    free_split(space_split);
}
// STILL NO BOUND CHECKS! be careful
// STILL NO BOUND CHECKS! be careful
void    parse_ambient(t_data *data, char *line)
{
    // A 0.2 255,255,255
    // ambient lighting ratio in the range [0.0,1.0]: 0.2
    // R, G, B colors in the range [0-255]: 255, 255, 255
    
    char	**space_split;
	char	**comma_split;

	space_split = ft_split(line, ' ');
	if (!space_split || !space_split[1] || !space_split[2])
		return ;
	comma_split = ft_split(space_split[2], ',');
	if (!comma_split || !comma_split[0] || !comma_split[1] || !comma_split[2])
	{
		free_split(space_split);
		free_split(comma_split);
		return ;
	}
    data->scene.ambient_light.intensity = ft_atof(space_split[1]);
    data->scene.ambient_light.color = (t_color){
        ft_atoi(comma_split[0]),
        ft_atoi(comma_split[1]),
        ft_atoi(comma_split[2])
    };
	free_split(space_split);
	free_split(comma_split);
}
