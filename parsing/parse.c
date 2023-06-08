/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:37:26 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/08 22:16:35 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include "get_next_line.h"

//check if we need typedef for norm ?
enum position
{
	first, middle, last
};

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

int		init_map(t_map *map)
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

	return 1;
}

int		check_file(char *file)
{
	//add ft_
	if(strncmp(file + strlen(file) - 4, ".cub", 4) != 0)
		return (printf("Error\nInvalid file extension") && 0);
	return (1);
}

int		validate_map_line(char *line)
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
		if (line[i + 1] == '\0' && line[i] != '1' && line[i] != ' ') //if next - eol, curr should be 1 or space
			return (printf("Error\nInvalid map!\n") & 0);
		if (i > 0 && line[i] == ' ' && line[i - 1] != '1' && line[i - 1] != ' ') // prev of space can be only 1 or space
			return (printf("Error\nInvalid map!\n") & 0);
	}

	return 1;
}

int		get_width_height(int fd, t_map *map)
{
	char *buf = NULL;
	int len;

	buf = get_next_line(fd);
	while (buf)
	{
		map->mapY += 1;
		len = strlen(buf) - 1;
		if (len <= 1)
			return (printf("Error\nInvalid map!\n") & 0);
		if (len > map->mapX)
			map->mapX = len;
		free(buf);
		buf = get_next_line(fd);
	}
	free(buf);
	close(fd);
	if (map->mapY < 3)
		return (printf("Error\nInvalid map!\n") & 0);
	return 1;
}

int		create_int_map(t_map *map)
{
	int *mapp;

	//TODO malloc protect
	mapp = malloc(sizeof(int) * map->mapX * map->mapY);
	if (!mapp)
		return (printf("Error\nMalloc error\n") & 0);
	map->map = mapp;
	return 1;
}

void	add_player(char *buff, t_map *map, int *tmp, int i)
{
	map->map[*tmp + i] = 0;
	map->player.dir = buff[i];
	map->player.x = i;
	map->player.y = (*tmp + i) / map->mapX;
}

int		add_in_map(char *buff, t_map *map, int *tmp)
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

int		get_textures(int fd, t_map *map)
{
	char	*buf = NULL;
	int i = 5;
	int len;

	buf = get_next_line(fd);

	// TODO ft_
	while (buf && --i > 0)
	{
		len = strlen(buf);
		if (len > 1 && buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strncmp(buf, "NO ", 3) == 0)
			map->no = strdup(&(buf[3]));
		else if (strncmp(buf, "SO ", 3) == 0)
			map->so = strdup(&(buf[3]));
		else if (strncmp(buf, "WE ", 3) == 0)
			map->we = strdup(&(buf[3]));
		else if (strncmp(buf, "EA ", 3) == 0)
			map->ea = strdup(&(buf[3]));
		else
		{
			free(buf);
			return (printf("Error\nWrong textures\n") & 0);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	if (strlen(buf) != 1 && buf[0] != '\n')
	{
		free(buf);
		return (printf("Error\nExtra symbols in file!\n") & 0);
	}
	free(buf);
	return 1;
}

/********** rgb **********/
//r = 1, g = 2, b = 3
int		check_rgb(char *rgb, int colour)
{
	//printf("rgb:%s:\n", rgb);
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
		if (rgb[1] != ',' && rgb[2] != ',' && rgb[3] != '\0')
			return (printf("Error\nWrong colours -7\n") & 0);
	}
	return 1;
}

int		write_rgb(char *rgb, t_map *map, char where, int colour)
{
	if (colour == 4)
		return 1;
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
		return 0;
	return write_rgb(rgb, map, where,colour + 1);
}

int		get_colours(int fd, t_map *map)
{
	char	*buf = NULL;
	char	*rgb = NULL;
	int i = 3;
	int len;

	buf = get_next_line(fd);

	// TODO ft_
	while (buf && --i > 0)
	{
		len = strlen(buf);
		if (len < 7 || len > 13)
		{
			free(buf);
			return (printf("Error\nWrong colours - len ?_?\n") & 0);
		}
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strncmp(buf, "F ", 2) == 0 || strncmp(buf, "C ", 2) == 0)
		{
			rgb = &(buf[2]);
			if (!check_rgb(rgb, 1)) return 0;
			if (buf[0] == 'F' && !write_rgb(rgb, map, 'F' ,1))
				return 0;
			else if (!write_rgb(rgb, map, 'C' ,1))
				return 0;
		}
		else
		{
			free(buf);
			return (printf("Error\nWrong colours - else\n") & 0);
		}
		free(buf);
		buf = get_next_line(fd);
	}
	if (strlen(buf) != 1 && buf[0] != '\n')
	{
		free(buf);
		return (printf("Error\nExtra symbols in file!\n") & 0);
	}
	free(buf);
	return 1;

}

int		check_colours(t_map *map)
{
	if (map->floor.r > 255 || map->floor.g > 255 || map->floor.b > 255 ||
		map->ceiling.r > 255 || map->ceiling.g > 255 || map->ceiling.b > 255)
	{
		return (printf("Error\nIncorrect colour value!\n") & 0);
	}
	return 1;
}
/*******************/

int		scroll_to_map(int fd)
{
	int i = 9;
	char *buf = NULL;

	while (--i)
	{
		buf = get_next_line(fd);
		if (!buf)
			return (printf("Error\nGNL error.\n") & 0);
		free(buf);
	}
	return 1;
}

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

/****** map ******/
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
/************/

int main(int ac, char *av[])
{
	t_map map;
	char *buf = NULL;

	int fd;
	int len;
	int tmp = 0;

	if (ac != 2)
		return (printf("Error\nWrong number of arguments") & 0);
	if (!check_file(av[1]))
		return (0);

	init_map(&map);

	/***********	here parse textures and colors *************************/
	fd = open(av[1], O_RDONLY);

	if (!get_textures(fd, &map) || !get_colours(fd, &map) ||
		!check_colours(&map) || !get_width_height(fd, &map)) {
		close(fd);
		return 0;
	}

	//TODO validate texture files.

	printf("\ttextures:\n NO:%s\n SO:%s\n WE:%s\n EA:%s\n",
		   map.no, map.so, map.we, map.ea);

	printf("\tcolors:\n F:%d,%d,%d C:%d,%d,%d\n",
		   map.floor.r, map.floor.g, map.floor.b, map.ceiling.r, map.ceiling.g, map.ceiling.b);

	/******************	map	*******************/

	// TODO move to function

	printf("mapX: %d mapY: %d\n\n", map.mapX, map.mapY);

	if (!create_int_map(&map))
		return 0;

	fd = open(av[1], O_RDONLY);
	if (!scroll_to_map(fd))
	{
		close(fd);
		return 0;
	}

	buf = get_next_line(fd);
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
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
	if (map.player.dir == 127)
		return (printf("Error\nYou cannot be without player\n") & 0);

	printf("player: x[%d], y[%d], direction[%c]\n", map.player.x, map.player.y, map.player.dir);

	if (!validate_walls(&map))
		return 0;

	//print_map(&map);
	return 0;
}

//cc parse.c get_next_line.c get_next_line_utils.c && ./a.out 0.cub