/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:23:13 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:09:20 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	freebuf_closefd(char *buf, int fd)
{
	if (buf)
		free(buf);
	close(fd);
	return (0);
}

int	free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->ea)
		free(map->ea);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->map)
		free(map->map);
	return (0);
}
