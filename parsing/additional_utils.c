/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:51:39 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:30:11 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_map_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' \
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' \
			&& line[i] != 'W')
			return (printf("Error\nWrong symbol on map!\n") & 0);
		if (i == 0 && line[i] != ' ' && line[i] != '1')
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i - 1] == ' ' && line[i] != '1' && line[i] != ' ')
			return (printf("Error\nInvalid map!\n") & 0);
		if (line[i + 1] == '\0' && line[i] != '1' && line[i] != ' ')
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ')
			return (printf("Error\nInvalid map!\n") & 0);
	}
	return (1);
}

int	check_file(char *file)
{
	if (strncmp(file + strlen(file) - 4, ".cub", 4) != 0)
		return (printf("Error\nInvalid file extension\n") && 0);
	return (1);
}

int	skip_spaces(char *buf, int i)
{
	while (buf[++i])
		if (buf[i] != ' ')
			break ;
	return (i);
}

int	scroll_to_map(int fd, int how_long)
{
	char	*buf;

	buf = NULL;
	while (--how_long)
	{
		buf = get_next_line(fd);
		if (!buf)
			return (printf("Error\nGNL error.\n") & 0);
		free(buf);
	}
	return (1);
}

int	mapline(char *buf)
{
	int		i;
	size_t	all_spaces;

	i = -1;
	all_spaces = 0;
	while (buf[++i])
	{
		if (buf[i] == ' ')
			all_spaces += 1;
		else if (buf[i] == '1' || buf[i] == '0')
			continue ;
		else
			return (0);
	}
	if (all_spaces == strlen(buf))
		return (printf("Error\nInvalid map: all spaces in a row\n") & 0);
	return (1);
}
