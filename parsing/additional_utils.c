/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:51:39 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/12 20:26:10 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file(char *file)
{
	//add ft_
	if(strncmp(file + strlen(file) - 4, ".cub", 4) != 0)
		return (printf("Error\nInvalid file extension") && 0);
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
	char *buf = NULL;

	while (--how_long)
	{
		buf = get_next_line(fd);
		if (!buf)
			return (printf("Error\nGNL error.\n") & 0);
		free(buf);
	}
	return 1;
}

int	mapline(char *buf)
{
	int i = -1;
	int all_spaces = 0;
	while (buf[++i])
	{
		if (buf[i] == ' ')
			all_spaces += 1;
		else if (buf[i] == '1' || buf[i] == '0')
			continue;
		else
			return 0;
	}
	if (all_spaces == strlen(buf))
		return (printf("Error\nInvalid map: all spaces in a row\n") & 0);
	return 1;
}
