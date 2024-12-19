/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:48:31 by mjong             #+#    #+#             */
/*   Updated: 2024/12/18 15:07:16 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flush_buffer(t_buffer *buf, int fd)
{
	if (buf->buf_index > 0)
	{
		write(fd, buf->buffer, buf->buf_index);
		buf->buf_index = 0;
	}
}

int	ft_setvbuf(t_buffer *buf, int mode)
{
	buf->buffer = (char *)malloc(BUFSIZE);
	if (!buf->buffer)
		return (-1);
	buf->buf_size = BUFSIZE;
	buf->buf_index = 0;
	buf->mode = mode;
	return (0);
}

ssize_t	custom_write(int fd, const void *data, size_t count, t_buffer *buffer)
{
	const char	*buf;
	size_t		i;

	buf = (const char *)data;
	i = 0;
	if (buffer->mode == 1)
	{
		while (i < count)
		{
			if (buffer->buf_index == buffer->buf_size)
				flush_buffer(buffer, fd);
			buffer->buffer[buffer->buf_index++] = buf[i++];
			if (buf[i - 1] == '\n')
				flush_buffer(buffer, fd);
		}
	}
	else
		return (write(fd, buf, count));
	return (count);
}
