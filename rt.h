/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:13:15 by emgenc            #+#    #+#             */
/*   Updated: 2025/08/10 01:13:28 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "minilibx/mlx.h"
# include "e-libft/libft.h"

# include <fcntl.h>     // open, close
# include <unistd.h>    // read, write
# include <stdlib.h>    // malloc, free, exit
# include <stdio.h>     // printf
# include "objects.h"
# include "color.h"
# include "camera.h"
# include "light.h"

# ifndef W_WIDTH
#  define W_WIDTH 3840
# endif

# ifndef __USE_MISC
#  define __USE_MISC
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 2160
# endif

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_objects		*all_objects;
	int				num_objects;
}	t_scene;

typedef struct s_data
{
	t_scene	scene;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		shutdown_lock_active;
}	t_data;

void	drawscene(t_data *data);

#endif