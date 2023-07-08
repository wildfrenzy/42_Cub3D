/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:41 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/08 15:48:05 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(mlx_t	*mlx, mlx_image_t **img, char *file)
{
	xpm_t	*texture;

	texture = mlx_load_xpm42(file);
	if (!texture)
	{
		perror("Error\n");
		return (0);
	}
	*img = mlx_texture_to_image(mlx, &(texture->texture));
	mlx_delete_xpm42(texture);
	return (1);
}

int	prepare_textures(t_cub *cub)
{
	if (!load_texture(cub->mlx, &(cub->map.north), cub->map.no))
		return (0);
	if (!load_texture(cub->mlx, &(cub->map.south), cub->map.so))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		return (0);
	}
	if (!load_texture(cub->mlx, &(cub->map.east), cub->map.ea))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		return (0);
	}
	if (!load_texture(cub->mlx, &(cub->map.west), cub->map.we))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		mlx_delete_image(cub->mlx, cub->map.east);
		return (0);
	}
	return (1);
}
