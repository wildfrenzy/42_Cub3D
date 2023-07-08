/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:43:21 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:33:49 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_texture(t_map *map, char texture, char *buf)
{
	int	i;

	if (!check_if_texture_exists(map, texture))
		return (0);
	i = 0;
	if (buf[0] == ' ')
		i = skip_spaces(buf, i - 1);
	if (texture == 'N')
		map->no = ft_strdup(&(buf[i]));
	else if (texture == 'S')
		map->so = ft_strdup(&(buf[i]));
	else if (texture == 'W')
		map->we = ft_strdup(&(buf[i]));
	else if (texture == 'E')
		map->ea = ft_strdup(&(buf[i]));
	if ((texture == 'N' && !map->no) || \
		(texture == 'S' && !map->so) || \
		(texture == 'W' && !map->we) || \
		(texture == 'E' && !map->ea))
		return (printf("Error\nTexture Error\n") & 0);
	map->all_info += 1;
	return (1);
}

int	check_if_texture_exists(t_map *map, char texture)
{
	if (texture == 'N' && map->no != NULL)
		return (printf("Error\nTexture for NO already exists!\n") & 0);
	else if (texture == 'S' && map->so != NULL)
		return (printf("Error\nTexture for SO already exists!\n") & 0);
	else if (texture == 'W' && map->we != NULL)
		return (printf("Error\nTexture for WE already exists!\n") & 0);
	else if (texture == 'E' && map->ea != NULL)
		return (printf("Error\nTexture for EA already exists!\n") & 0);
	return (1);
}
