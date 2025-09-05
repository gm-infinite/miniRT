/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:11:26 by emgenc            #+#    #+#             */
/*   Updated: 2025/09/05 20:17:18 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline unsigned short	ft_error(void)
{
	perror("Error\n");
	return (1);
}

int	graceful_exit(t_data *data)
{
	if (data->shutdown_lock_active)
		return (0);
	data->shutdown_lock_active = 1;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}

void	ft_init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	data->shutdown_lock_active = 0;
	mlx_hook(data->win, 17, 0, *graceful_exit, data);
	
	data->scene.all_objects = malloc(sizeof(t_object_item) * 4);
	// check malloc!!!!!!
	drawscene(data);
	mlx_loop(data->mlx);
}

/*
	The program displays the image in a window and respects the following rules:
	1. Pressing ESC must close the window and quit the program cleanly.
	2. Clicking on the red cross on the window frame must close the window
	   and quit the program cleanly.
	3. The use of images from the minilibX library is strongly recommended.

	• Your program must take as its first argument as
	  a scene description file with the .rt extension.
	• Each type of element can be separated by one or more line breaks.
	• Each type of information from an element can be separated by one or more spaces.
	• Each type of element can be set in any order in the file.
	• Elements defined by a capital letter can only be declared once in the scene.
	• The first piece of information for each element is the type identifier (composed of one or two characters),
	  followed by all specific information for each object in a strict order.
	• If any misconfiguration of any kind is encountered in the file,
	  the program must exit properly and return "Error\n" followed by an explicit error message of your choice.
*/

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;
	//char	*line_parser;

	if (argc == 2)
	{
		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) == 0)
		{
			fd = open(argv[1], O_RDONLY);
			if (fd < 0)
				return (ft_error());
			ft_init_data(&data);
			parse();
			
			//
			close(fd);
			//
			
			return (0);
		}
	}
	return (0);
}
