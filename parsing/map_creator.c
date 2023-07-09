/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <nmaliare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:46:29 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/09 13:06:50 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_int_map(t_map *map)
{
	int	*mapp;

	map->mapsize = map->map_x * map->map_y;
	mapp = malloc(sizeof(int) * map->mapsize);
	if (!mapp)
		return (printf("Error\nMalloc error\n") & 0);
	map->map = mapp;
	return (1);
}

int	get_width_height(int fd, t_map *map, char *buf)
{
	int		len;
	char	end;

	while (buf)
	{
		map->map_y += 1;
		len = ft_strlen(buf) - 1;
		end = buf[len];
		if (len <= 1)
		{
			freebuf_closefd(buf, fd);
			return (printf("Error\nInvalid map!>\n") & 0);
		}
		if (len > map->map_x)
			map->map_x = len;
		free(buf);
		buf = get_next_line(fd);
	}
	freebuf_closefd(buf, fd);
	if (map->map_y < 3 || end == '\n')
		return (printf("Error\nInvalid map!\n") & 0);
	return (1);
}

int	add_in_map(char *buff, t_cub *cub, int *tmp)
{
	int	i;

	i = -1;
	while (buff[++i])
	{
		if (buff[i] == '1')
			cub->map.map[*tmp + i] = 1;
		else if (buff[i] == '0')
			cub->map.map[*tmp + i] = 0;
		else if (buff[i] == ' ')
			cub->map.map[*tmp + i] = -1;
		else if (cub->map.pos.dir != 127 && (buff[i] == 'S' || buff[i] == 'E' \
			|| buff[i] == 'W' || buff[i] == 'N'))
			return (printf("Error\nYou cannot have more than 1 player!\n") & 0);
		else if (cub->map.pos.dir == 127 && (buff[i] == 'S' || buff[i] == 'E' \
			|| buff[i] == 'W' || buff[i] == 'N'))
			add_player(buff, cub, tmp, i);
	}
	while (i < cub->map.map_x)
	{
		cub->map.map[*tmp + i] = -1;
		i++;
	}
	*tmp += i;
	return (1);
}

void	add_player(char *buff, t_cub *cub, int *tmp, int i)
{
	cub->map.map[*tmp + i] = 0;
	cub->map.pos.dir = buff[i];
	cub->map.pos.x = i;
	cub->map.pos.y = (*tmp + i) / cub->map.map_x;
}
