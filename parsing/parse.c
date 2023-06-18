/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:37:26 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/18 21:07:35 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_map(t_map *map)
{
	int j = -1;
	int all = map->mapX * map->mapY;
	printf("\nMAP:\n");
	while (++j < all)
	{
		if (j % (all / map->mapY) == 0)
			printf("\n[%d]", map->map[j]);
		else
			printf("[%d]", map->map[j]);
	}
	printf("\n\nall[%d]\n", all);
}

int		first_read_till_map(t_map *map, char *buf)
{
	if (strncmp(buf, "F ", 2) == 0 || strncmp(buf, "C ", 2) == 0)
	{
		if (!get_colour(map, buf[0], &(buf[1])))
			return 0;
	}
	else if (strncmp(buf, "NO ", 3) == 0 || strncmp(buf, "SO ", 3) == 0 ||
			 strncmp(buf, "WE ", 3) == 0 || strncmp(buf, "EA ", 3) == 0)
	{
		if (!get_texture(map, buf[0], &(buf[2])))
			return 0;
	}
	else if (buf[0] != '\0')
		return (printf("Error\nExtra symbols in file\n") & 0);
	return  1;
}

int		gather_data(t_map *map, char *av, int *lines)
{
	int fd;
	int len;
	char *buf;

	fd = open(av, O_RDONLY);
	buf = get_next_line(fd);
	while (buf)
	{
		len = strlen(buf); //ft_
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (map->all_info != 6 && !first_read_till_map(map, buf))
			return (freebuf_closefd(buf, fd));
		else if (map->all_info == 6 && buf[0] != '\0') // got all info. rolling to map
		{
			if (mapline(buf))
			{
				if (!check_colours(map))
					return (freebuf_closefd(buf, fd));
				if (!get_width_height(fd, map, buf))
					return (0);
				break ;
			}
		}
		free(buf);
		*lines += 1;
		buf = get_next_line(fd);
	}
	return 1;
}

int		fill_that_map(t_map *map, char *file, int how_long_till_map)
{
	int fd;
	int len;
	int tmp;
	char *buf;

	tmp = 0;
	fd = open(file, O_RDONLY);
	if (!scroll_to_map(fd, how_long_till_map))
		return close(fd);
	buf = get_next_line(fd);
	while (buf)
	{
		len = strlen(buf); //ft_
		if(buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (!validate_map_line(buf) || !add_in_map(buf, map, &tmp))
			return (freebuf_closefd(buf, fd));
		free(buf);
		buf = get_next_line(fd);
	}
	freebuf_closefd(buf, fd);
	if (map->player.dir == 127)
		return (printf("Error\n") & 0);
	return 1;
}

int main(int ac, char *av[])
{
	t_map map;
	int how_long_till_map = 1;

	if (ac != 2)
		return (printf("Error\nWrong number of arguments\n") & 0);
	if (!check_file(av[1]))
		return (0);

	init_map(&map);

	if (!gather_data(&map, av[1], &how_long_till_map) || !create_int_map(&map) ||
		!fill_that_map(&map, av[1], how_long_till_map) || !validate_walls(&map))
		return free_map(&map);

	printf("\nAll info: %d\nTill map: %d\n", map.all_info, how_long_till_map);
	printf("\ttextures:\n NO:%s\n SO:%s\n WE:%s\n EA:%s\n",
		   map.no, map.so, map.we, map.ea);
	printf("\tcolors:\n F:%d,%d,%d C:%d,%d,%d\n",
		   map.floor.r, map.floor.g, map.floor.b, map.ceiling.r, map.ceiling.g, map.ceiling.b);
	printf("mapX: %d mapY: %d\n\n", map.mapX, map.mapY);
	printf("player: x[%d], y[%d], direction[%c]\n", map.player.x, map.player.y, map.player.dir);
	//TODO validate texture files.
	return free_map(&map);
}

//cc parse.c parse_map.c parse_colours.c parse_textures.c map_creator.c additional_utils.c freedom.c get_next_line.c get_next_line_utils.c && ./a.out 0.cub