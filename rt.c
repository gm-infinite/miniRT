/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:11:26 by emgenc            #+#    #+#             */
/*   Updated: 2025/08/10 01:20:33 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

static int	ft_error(char *str)
{
	printf("Error\n%s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_error("Invalid number of arguments."));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
		return (ft_error("Invalid file extension. Expected .rt file."));
	return (0);
}
