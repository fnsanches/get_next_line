/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsanches <fsanches@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:21:01 by fsanches          #+#    #+#             */
/*   Updated: 2022/04/22 15:21:51 by fsanches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// get_next_line()

// get_next_line() returns a line from a file descriptor.

// Return value is the read line, or NULL if there is nothing to read, or an
// error occurred.

#include "get_next_line.h"

static char	*read_file(int fd, char *save)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(save, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			break ;
		buffer[read_bytes] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	if (read_bytes < 0)
		return (NULL);
	else
		return (save);
}

static char	*get_line(char *save)
{
	char	*line;
	size_t	size;

	if (!*save)
		return (NULL);
	size = 0;
	while (save[size] && save[size] != '\n')
		size++;
	line = (char *)malloc((size + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, size + 1);
	if (save[size] == '\n')
		line[size++] = '\n';
	line[size] = '\0';
	return (line);
}

static char	*rmv_read_line(char *save)
{
	int		i;
	int		j;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new_save = (char *)malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!new_save)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = rmv_read_line(save);
	return (line);
}
