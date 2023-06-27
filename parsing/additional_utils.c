/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:51:39 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/26 21:24:56 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	size_t all_spaces = 0;
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

