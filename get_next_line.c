/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:12:37 by emgenc            #+#    #+#             */
/*   Updated: 2025/10/05 12:13:10 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "e-libft/libft.h"
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static char	*ft_strjoin_strcat(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		*s1 = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcpy(str + ft_strlen(str), s2, ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

static char	*ft_read_file(char *retain, int fd)
{
	int		i;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	i = 0;
	if (!retain)
		retain = ft_strdup("");
	while (!ft_strchr(retain, '\n') && ++i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1 || (i == 0 && ft_strlen(retain) == 0))
		{
			if (retain)
				free(retain);
			return (free(temp), NULL);
		}
		temp[i] = '\0';
		retain = ft_strjoin_strcat(retain, temp);
		i--;
	}
	return (free(temp), retain);
}

static void	ft_assign(char **retain, char **line)
{
	int		i;
	char	*initial_retain;

	i = 0;
	initial_retain = *retain;
	while ((*retain)[i] != '\n' && (*retain)[i] != '\0')
		i++;
	*line = ft_substr(*retain, 0, i + 1);
	if (!**retain)
		return (*retain = NULL, free(*retain));
	*retain = ft_substr(*retain, i + 1,
			ft_strlen(ft_strchr(*retain, '\n')));
	free(initial_retain);
}

char	*get_next_line(int fd, int eof)
{
	static char	*retain[1024];
	char		*line;

	if (eof == -1)
	{
		if (fd < 0 || fd >= 1024)
			return (NULL);
		if (retain[fd])
		{
			free(retain[fd]);
			retain[fd] = NULL;
			return (NULL);
		}
	}
	if (fd < 0 || BUFFER_SIZE < 0 || fd > 1024)
		return (NULL);
	retain[fd] = ft_read_file(retain[fd], fd);
	if (!retain[fd] || !*retain[fd])
		return (NULL);
	ft_assign(&(retain[fd]), &line);
	return (line);
}
