/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:20:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static char	*flush(t_gnl *gnl, char *newline, size_t line_size, size_t new_size)
{
	if (!gnl->line)
		return (gnl->line);
	if (gnl->line && newline)
	{
		ft_memmove(gnl->buffer, newline + 1,
			gnl->size - ((size_t)newline - (size_t)gnl->buffer + 1));
		gnl->buffer[gnl->size - (new_size - line_size)] = 0;
		gnl->size = gnl->size - (new_size - line_size);
	}
	if (gnl->size < 0)
	{
		free(gnl->line);
		gnl->line = 0;
	}
	else if (newline)
		gnl->line = ft_memtostr(gnl->line, line_size + (new_size - line_size));
	else
		gnl->line = ft_memtostr(gnl->line, new_size);
	return (gnl->line);
}

static char	*join_buffer(t_gnl *gnl, size_t line_size, size_t new_size)
{
	gnl->line = ft_reallocf(gnl->line, line_size, new_size);
	if (!gnl->line)
		return (0);
	ft_memmove(gnl->line + line_size, gnl->buffer, new_size - line_size);
	return (gnl->line);
}

static char	*get_line(t_gnl *gnl)
{
	size_t	line_size;
	size_t	new_size;
	char	*newline;

	gnl->line = 0;
	line_size = 0;
	newline = 0;
	if (!gnl->size)
		gnl->size = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
	while (!newline && gnl->size > 0)
	{
		newline = ft_memchr(gnl->buffer, '\n', gnl->size);
		if (newline)
			new_size = line_size + ((size_t)newline - (size_t)gnl->buffer) + 1;
		else
			new_size = line_size + gnl->size;
		if (!join_buffer(gnl, line_size, new_size))
			return (0);
		if (!newline)
		{
			line_size += gnl->size;
			gnl->size = read(gnl->fd, gnl->buffer, BUFFER_SIZE);
		}
	}
	return (flush(gnl, newline, line_size, new_size));
}

char	*ft_get_next_line(int fd)
{
	static t_gnl	gnl[257];

	if (fd < 0 || fd > 256)
		return (0);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0))
	{
		gnl[fd].buffer[0] = 0;
		gnl[fd].size = 0;
		return (0);
	}
	gnl[fd].fd = fd;
	gnl[fd].line = get_line(&(gnl[fd]));
	if (!gnl[fd].line)
	{
		gnl[fd].buffer[0] = 0;
		gnl[fd].size = 0;
	}
	return (gnl[fd].line);
}
