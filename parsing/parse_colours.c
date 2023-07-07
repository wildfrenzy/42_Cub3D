/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:38:29 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:17:52 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_rgb(char *rgb, int colour)
{
	if (colour == 1 || colour == 2)
	{
		if (rgb[0] < '0' || rgb[0] > '9')
			return (printf("Error\nWrong colours - 0\n") & 0);
		if ((rgb[1] < '0' || rgb[1] > '9') && rgb[1] != ',' )
			return (printf("Error\nWrong colours - 1\n") & 0);
		if ((rgb[2] < '0' || rgb[2] > '9') && rgb[2] != ',')
			return (printf("Error\nWrong colours - 2\n") & 0);
		if (rgb[1] != ',' && rgb[2] != ',' && rgb[3] != ',')
			return (printf("Error\nWrong colours - 3\n") & 0);
	}
	else if (colour == 3)
	{
		if (rgb[0] < '0' || rgb[0] > '9')
			return (printf("Error\nWrong colours - 4\n") & 0);
		if ((rgb[1] < '0' || rgb[1] > '9') && rgb[1] != '\0')
			return (printf("Error\nWrong colours - 5\n") & 0);
		if ((rgb[2] < '0' || rgb[2] > '9') && rgb[2] != '\0')
			return (printf("Error\nWrong colours - 6\n") & 0);
		if (rgb[1] != ',' && rgb[2] && rgb[2] != ',' && rgb[3] != '\0')
			return (printf("Error\nWrong colours -7\n") & 0);
	}
	return (1);
}

int	check_colours(t_map *map)
{
	if (map->floor.r > 255 || map->floor.g > 255 || map->floor.b > 255 || \
		map->ceiling.r > 255 || map->ceiling.g > 255 || map->ceiling.b > 255 || \
		map->floor.r < 0 || map->floor.g < 0 || map->floor.b < 0 || \
		map->ceiling.r < 0 || map->ceiling.g < 0 || map->ceiling.b < 0)
		return (printf("Error\nIncorrect colour value!\n") & 0);
	return (1);
}

int	get_colour(t_map *map, char color, char *buf)
{
	int		i;
	char	*rgb;

	i = 0;
	rgb = NULL;
	if (buf[0] == ' ')
		i = skip_spaces(buf, i - 1);
	rgb = &(buf[i]);
	if (!check_rgb(rgb, 1) || !write_rgb(rgb, map, color, 1))
		return (0);
	map->all_info += 1;
	return (1);
}

int	write_rgb(char *rgb, t_map *map, char where, int colour)
{
	if (colour == 4)
		return (1);
	if (where == 'F')
	{
		if (colour == 1)
			map->floor.r = atoi(rgb);
		else if (colour == 2)
			map->floor.g = atoi(rgb);
		else if (colour == 3)
			map->floor.b = atoi(rgb);
	}
	else
	{
		if (colour == 1)
			map->ceiling.r = atoi(rgb);
		else if (colour == 2)
			map->ceiling.g = atoi(rgb);
		else if (colour == 3)
			map->ceiling.b = atoi(rgb);
	}
	rgb = strchr(rgb, ',');
	rgb += 1;
	if (colour + 1 < 4 && !check_rgb(rgb, colour + 1))
		return (0);
	return (write_rgb(rgb, map, where, colour + 1));
}
