/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:30:37 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/12 18:38:22 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		validate_map_line(char *line)
{
	int i = -1;

	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W') //general symbol check
			return (printf("Error\nWrong symbol on map!\n") & 0);
		if (i == 0 && line[i] != ' ' && line[i] != '1') //starts with space or 1 ?
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i-1] == ' ' && line[i] != '1' && line[i] != ' ') //if prev is space, next should be space or 1
			return (printf("Error\nInvalid map!\n") & 0);
		if (line[i + 1] == '\0' && line[i] != '1' && line[i] != ' ') //if next - eol, curr should be 1 or space
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ') // prev of space can be only 1 or space
			return (printf("Error\nInvalid map!\n") & 0);
	}

	return 1;
}

int		check_top(t_map *map, int i, int position)
{
	int	top;

	top = i - map->mapX;
	if (map->map[top] == 0)
		return (printf("Error\nInvalid map - no top wall\n") & 0);
	if (position != first && map->map[top - 1] == 0)
		return (printf("Error\nInvalid map - no top-left wall\n") & 0);
	if (position != last && map->map[top + 1] == 0)
		return (printf("Error\nInvalid map - no top-right wall\n") & 0);
	return 1;
}

int		check_bot(t_map *map, int i, int position)
{
	int	bot;

	bot = i + map->mapX;
	if (map->map[bot] == 0)
		return (printf("Error\nInvalid map - no bot wall\n") & 0);
	if (position != first && map->map[bot - 1] == 0)
		return (printf("Error\nInvalid map - no bot-left wall\n") & 0);
	if (position != last && map->map[bot + 1] == 0)
		return (printf("Error\nInvalid map - no bot-right wall\n") & 0);
	return 1;
}

int		check_first_row(t_map *map)
{
	int i = -1;
	int all_spaces = 0;

	while (++i < map->mapX)
	{
		if (map->map[i] == 0)
			return (printf("Error\nInvalid map\n") & 0);
		else if (map->map[i] == -1)
		{
			all_spaces += 1;
			if (i == 0 && !check_bot(map, i, first))
				return 0;
			else if (i == map->mapX - 1 && !check_bot(map, i, last))
				return 0;
			else if (i != 0 && i != map->mapX - 1 && !check_bot(map, i, middle))
				return 0;
		}
	}
	if (all_spaces == map->mapX)
		return (printf("Error\nInvalid map - first row all spaces\n") & 0);

	return 1;
}

int		check_last_row(t_map *map)
{
	int i;
	int total = map->mapX * map->mapY;
	int all_spaces = 0;

	i = (map->mapX * (map->mapY - 1)) - 1;
	int tmp = i;

	while (++i < total)
	{
		if (map->map[i] == 0)
			return (printf("Error\nInvalid map\n") & 0);
		else if (map->map[i] == -1)
		{
			all_spaces += 1;
			if (i == tmp && !check_top(map, i, first))
				return 0;
			else if (i == tmp + map->mapX - 1 && !check_top(map, i, last))
				return 0;
			else if (i != tmp && i != tmp + map->mapX - 1 && !check_top(map, i, middle))
				return 0;
		}
	}
	if (all_spaces == map->mapX)
		return (printf("Error\nInvalid map - last row all spaces\n") & 0);
	return 1;
}

int		validate_walls(t_map *map)
{
	int i = map->mapX - 1; //last of 1st row
	long size = map->mapX * (map->mapY - 1);

	if (!check_first_row(map))
		return 0;

	//we start with 1 element 2nd row
	while (++i < size)
	{
		if (map->map[i] == -1)
		{
			if (i % map->mapX == 0 && (!check_top(map, i, first) || !check_bot(map, i, first)))
				return 0;
			else if (i % map->mapX == map->mapX - 1 && (!check_top(map, i, last) || !check_bot(map, i, last)))
				return 0;
			else if (i % map->mapX != 0 && i % map->mapX != map->mapX - 1 && (!check_top(map, i, middle) || !check_bot(map, i, middle)))
				return 0;
		}
	}
	if (!check_last_row(map))
		return 0;
	return 1;
}
