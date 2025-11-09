/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuzyilma <kuzyilma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:11:26 by emgenc            #+#    #+#             */
/*   Updated: 2025/11/02 13:33:47 by kuzyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <X11/keysym.h>

static inline unsigned short	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}

static int	graceful_exit(t_data *data)
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
	if (data->scene.all_objects)
		free(data->scene.all_objects);
	exit(0);
}

static int	keyboard_hooks(int pressed_key, t_data *data)
{
	if (pressed_key == XK_Escape)
		graceful_exit(data);
	return (0);
}

static void	ft_init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	data->shutdown_lock_active = 0;
	mlx_key_hook(data->win, keyboard_hooks, data);
	mlx_hook(data->win, 17, 0, *graceful_exit, data);
	drawscene(data);
	printf("Rendering complete. Press ESC or close the window to exit.\n");
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_error("Usage: ./miniRT <scene.rt>"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
		return (ft_error("Invalid file extension (must be .rt)"));
	if (!parse(&data, argv[1]))
		return (ft_error("Invalid scene file"));
	printf("%d objects parsed\n", data.scene.num_objects);
	ft_init_data(&data);
	drawscene(&data);
	mlx_loop(data.mlx);
	return (0);
}
