/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:37:26 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:37:23 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	first_read_till_map(t_map *map, char *buf)
{
	if (strncmp(buf, "F ", 2) == 0 || strncmp(buf, "C ", 2) == 0)
	{
		if (!get_colour(map, buf[0], &(buf[1])))
			return (0);
	}
	else if (ft_strncmp(buf, "NO ", 3) == 0 || ft_strncmp(buf, "SO ", 3) == 0 ||
			 ft_strncmp(buf, "WE ", 3) == 0 || ft_strncmp(buf, "EA ", 3) == 0)
	{
		if (!get_texture(map, buf[0], &(buf[2])))
			return (0);
	}
	else if (buf[0] != '\0')
		return (printf("Error\nExtra symbols in file\n") & 0);
	return (1);
}

int	gather_data(t_map *map, char *av, int *lines)
{
	int		fd;
	int		len;
	char	*buf;

	fd = open(av, O_RDONLY);
	buf = get_next_line(fd);
	while (buf)
	{
		len = strlen(buf); //ft_
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (map->all_info != 6 && !first_read_till_map(map, buf))
			return (freebuf_closefd(buf, fd));
		else if (map->all_info == 6 && buf[0] != '\0')
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
	return (1);
}

int	fill_that_map(t_cub *cub, char *file, int how_long_till_map)
{
	int		fd;
	int		len;
	int		tmp;
	char	*buf;

	tmp = 0;
	fd = open(file, O_RDONLY);
	if (!scroll_to_map(fd, how_long_till_map))
		return (close(fd));
	buf = get_next_line(fd);
	while (buf)
	{
		len = ft_strlen(buf);
		if(buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (!validate_map_line(buf) || !add_in_map(buf, cub, &tmp))
			return (freebuf_closefd(buf, fd));
		free(buf);
		buf = get_next_line(fd);
	}
	freebuf_closefd(buf, fd);
	if (cub->map.pos.dir == 127)
		return (printf("Error\n") & 0);
	return (1);
}
