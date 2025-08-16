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

# ifndef W_WIDTH
#  define W_WIDTH 1000
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 1000
# endif

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		shutdown_lock_active;
}			t_data;

#endif