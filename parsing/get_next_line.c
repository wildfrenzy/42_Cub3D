/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 00:18:45 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/06 22:49:36 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *content)
{
	int		i;
	char	*str;

	i = 0;
	if (!content || !content[i])
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '\n')
	{
		str[i] = content[i];
		i++;
	}
	if (content[i] == '\n')
	{
		str[i] = content[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_read_to_content(int fd, char *content)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(content, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(content);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		content = ft_strjoin(content, buff);
	}
	free(buff);
	return (content);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*content[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	content[fd] = ft_read_to_content(fd, content[fd]);
	if (!content[fd])
		return (NULL);
	line = ft_get_line(content[fd]);
	content[fd] = ft_new_content(content[fd]);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	int fd = open("test.txt", O_RDONLY);
	char *str;
	while (1)
	{
		str = get_next_line(fd);
		printf("> %s", str);
		if (!str) break ;
		free(str);
	}
}
*/
