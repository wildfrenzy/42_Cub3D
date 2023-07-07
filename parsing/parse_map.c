/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:30:37 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:30:20 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_top(t_map *map, int i, int position)
{
	int	top;

	top = i - map->mapX;
	if (map->map[top] == 0)
		return (printf("Error\nInvalid map - no top wall\n") & 0);
	if (position != first && map->map[top - 1] == 0)
		return (printf("Error\nInvalid map - no top-left wall\n") & 0);
	if (position != last && map->map[top + 1] == 0)
		return (printf("Error\nInvalid map - no top-right wall\n") & 0);
	return (1);
}

int	check_bot(t_map *map, int i, int position)
{
	int	bot;

	bot = i + map->mapX;
	if (map->map[bot] == 0)
		return (printf("Error\nInvalid map - no bot wall\n") & 0);
	if (position != first && map->map[bot - 1] == 0)
		return (printf("Error\nInvalid map - no bot-left wall\n") & 0);
	if (position != last && map->map[bot + 1] == 0)
		return (printf("Error\nInvalid map - no bot-right wall\n") & 0);
	return (1);
}

int	check_first_row(t_map *map)
{
	int	i;
	int	all_spaces;

	i = -1;
	all_spaces = 0;
	while (++i < map->mapX)
	{
		if (map->map[i] == 0)
			return (printf("Error\nInvalid map\n") & 0);
		else if (map->map[i] == -1)
		{
			all_spaces += 1;
			if (i == 0 && !check_bot(map, i, first))
				return (0);
			else if (i == map->mapX - 1 && !check_bot(map, i, last))
				return (0);
			else if (i != 0 && i != map->mapX - 1 && !check_bot(map, i, middle))
				return (0);
		}
	}
	if (all_spaces == map->mapX)
		return (printf("Error\nInvalid map - first row all spaces\n") & 0);
	return (1);
}

int	check_last_row(t_map *map)
{
	int	i;
	int	total;
	int	all_spaces;
	int	tmp;

	total = map->mapX * map->mapY;
	i = (map->mapX * (map->mapY - 1)) - 1;
	all_spaces = 0;
	tmp = i;
	while (++i < total)
	{
		if (map->map[i] == 0)
			return (printf("Error\nInvalid map\n") & 0);
		else if (map->map[i] == -1)
		{
			all_spaces += 1;
			if ((i == tmp && !check_top(map, i, first)) || (i == tmp \
				+ map->mapX - 1 && !check_top(map, i, last)) || (i != tmp \
				&& i != tmp + map->mapX - 1 && !check_top(map, i, middle)))
				return (0);
		}
	}
	if (all_spaces == map->mapX)
		return (printf("Error\nInvalid map - last row all spaces\n") & 0);
	return (1);
}

int	validate_walls(t_map *map)
{
	int		i;
	long	size;

	i = map->mapX - 1;
	size = map->mapX * (map->mapY - 1);
	if (!check_first_row(map))
		return (0);
	while (++i < size)
	{
		if (map->map[i] == -1)
		{
			if (i % map->mapX == 0 && (!check_top(map, i, first) || \
				!check_bot(map, i, first)))
				return (0);
			else if (i % map->mapX == map->mapX - 1 && \
				(!check_top(map, i, last) || !check_bot(map, i, last)))
				return (0);
			else if (i % map->mapX != 0 && i % map->mapX != map->mapX - 1 \
				&& (!check_top(map, i, middle) || !check_bot(map, i, middle)))
				return (0);
		}
	}
	if (!check_last_row(map))
		return (0);
	return (1);
}
