/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:37:26 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/07 01:02:11 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include "get_next_line.h"

typedef struct s_player
{
	int	x;
	int	y;
	char	dir; //N,S,E,W
}				t_player;

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
}				t_colour;

typedef struct s_map
{
	int *map;
	int mapX;
	int mapY;
	char *no;
	char *so;
	char *we;
	char *ea;

	t_colour floor;
	t_colour ceiling;
	t_player player;
}				t_map;

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

	//TODO null check
	//map = malloc(sizeof(t_map ));
	//if (!map)
	//	return 0;

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

	return 1;
}

int	check_file(char *file)
{
	//add ft_
	if(strncmp(file + strlen(file) - 4, ".cub", 4) != 0)
		return (printf("Error\nInvalid file extension") && 0);
	return (1);
}

int	validate_map_line(char *line)
{
	int i = -1;

	// TODO check top of space should be 1
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W') //general symbol check
			return (printf("Error\nWrong symbol on map!\n") & 0);
		if (i == 0 && line[i] != ' ' && line[i] != '1') //starts with space or 1 ?
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i-1] == ' ' && line[i] != '1' && line[i] != ' ') //if prev is space, next should be space or 1
			return (printf("Error\nInvalid map!\n") & 0);
		if (line[i + 1] == '\0' && line[i] != '1') //if next - eol, curr should be 1
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ') // prev of space can be only 1 or space
			return (printf("Error\nInvalid map!\n") & 0);
	}

	return 1;
}

int	get_width_height(char *file, t_map *map)
{
	char *buf = NULL;
	int len;
	int fd;

	fd = open(file, O_RDONLY);
	buf = get_next_line(fd);

	//printf("start mapX:%d\n", map->mapX);

	while (buf)
	{
		map->mapY += 1;
		len = strlen(buf) - 1;
		//printf("len: %d, mapX:%d\nbuf:%s\n", len, map->mapX, buf);
		if (len <= 1)
			return (0);
		if (len > map->mapX)
			map->mapX = len;
		free(buf);
		buf = get_next_line(fd);
	}
	free(buf);
	close(fd);
	return 1;
}

int	create_int_map(t_map *map)
{
	int *mapp;

	//TODO malloc protect
	mapp = malloc(sizeof(int) * map->mapX * map->mapY);
	if (!mapp)
		return (printf("Error\nMalloc error\n") & 0);
	map->map = mapp;
	return 1;
}

void add_player(char *buff, t_map *map, int *tmp, int i)
{
	map->map[*tmp + i] = 0;
	map->player.dir = buff[i];
	map->player.x = i;
	map->player.y = (*tmp + i) / map->mapX;
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
		else if (map->player.dir == 127 && (buff[i] == 'S' || buff[i] == 'E' || buff[i] == 'W' || buff[i] == 'N')) //ask Barra if we mark player on the map or no. for now i don't.
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

int main(int ac, char *av[])
{
	t_map map;
	char *buf = NULL;

	int fd;
	int len = 0;
	int tmp = 0;

	if (ac != 2)
		return (printf("Error\nWrong number of arguments") & 0);
	if (!check_file(av[1]))
		return (0);

	init_map(&map);

	if (!get_width_height(av[1], &map))
		return (printf("Error\nInvalid map!\n") & 0);

	printf("mapX: %d mapY: %d\n", map.mapX, map.mapY);

	fd = open(av[1], O_RDONLY);
	buf = get_next_line(fd);

	if (!create_int_map(&map))
		return 0;
	while (buf)
	{
		len = strlen(buf); //ft_
		if(len > 1 && buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (!validate_map_line(buf) || !add_in_map(buf, &map, &tmp))
		{
			free(buf);
			return (0);
		}
		//printf("in map written: [%d] ints\n", tmp);
		free(buf);
		buf = get_next_line(fd);
	}
	printf("player: x[%d], y[%d], direction[%c]\n", map.player.x, map.player.y, map.player.dir);

	int j = -1;
	int all = map.mapX * map.mapY;
	printf("\nMAP:\n");
	while (++j < all)
	{
		if (j % (all / map.mapY) == 0)
			printf("\n");
		else
			printf("[%d]",map.map[j]);
	}
	printf("\n\nall[%d]\n", all);
	return 0;
}

//cc parse.c get_next_line.c get_next_line_utils.c && ./a.out 0.cub