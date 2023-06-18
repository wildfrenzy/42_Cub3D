/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:46:29 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/12 20:54:40 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_map(t_map *map)
{
	t_colour floor;
	t_colour ceiling;
	t_player player;

	floor.r = 0;
	floor.g = 0;
	floor.b = 0;

	ceiling.r = 0;
	ceiling.g = 0;
	ceiling.b = 0;

	player.x = 0;
	player.y = 0;
	player.dir = 127; // no direction

	map->player = player;
	map->floor = floor;
	map->ceiling = ceiling;
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->mapX = 0;
	map->mapY = 0;
	map->all_info = 0;

	return 1;
}

int	create_int_map(t_map *map)
{
	int *mapp;

	mapp = malloc(sizeof(int) * map->mapX * map->mapY);
	if (!mapp)
		return (printf("Error\nMalloc error\n") & 0);
	map->map = mapp;
	return 1;
}

int	get_width_height(int fd, t_map *map, char *buf)
{
	int len;

	while (buf)
	{
		map->mapY += 1;
		len = strlen(buf) - 1;
		if (len <= 1) {
			freebuf_closefd(buf, fd);
			return (printf("Error\nInvalid map!>\n") & 0);
		}
		if (len > map->mapX)
			map->mapX = len;
		free(buf);
		buf = get_next_line(fd);
	}
	freebuf_closefd(buf, fd);
	if (map->mapY < 3)
		return (printf("Error\nInvalid map!<\n") & 0);
	return 1;
}

int	add_in_map(char *buff, t_map *map, int *tmp)
{
	int i;

	i = -1;

	//printf("\ntmp:[%d] buff: %s\n", *tmp, buff);
	while (buff[++i])
	{
		if (buff[i] == '1')
			map->map[*tmp + i] = 1;
		else if (buff[i] == '0')
			map->map[*tmp + i] = 0;
		else if (buff[i] == ' ')
			map->map[*tmp + i] = -1;
		else if (map->player.dir != 127 && (buff[i] == 'S' || buff[i] == 'E' || buff[i] == 'W' || buff[i] == 'N'))
			return (printf("Error\nYou cannot have more than 1 player!\n") & 0);
		else if (map->player.dir == 127 && (buff[i] == 'S' || buff[i] == 'E' || buff[i] == 'W' || buff[i] == 'N'))
			add_player(buff, map, tmp, i);
	}
	//printf("\ni[%d], mapX[%d]\n", i, map->mapX);
	while (i < map->mapX)
	{
		map->map[*tmp + i] = -1; // -1
		i++;
	}
	*tmp += i;
	return (1);
}

void	add_player(char *buff, t_map *map, int *tmp, int i)
{
	map->map[*tmp + i] = 0;
	map->player.dir = buff[i];
	map->player.x = i;
	map->player.y = (*tmp + i) / map->mapX;
}
