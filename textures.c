/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:41 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/05 14:56:15 by nmaliare         ###   ########.fr       */
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
	printf("img: %dpx %dpx\n", (*img)->width, (*img)->height);
	mlx_delete_xpm42(texture);
	return 1;
}

void	resize_textures(t_cub *cub)
{
	mlx_resize_image(cub->map.north, cub->blockS, cub->blockS);
	mlx_resize_image(cub->map.south, cub->blockS, cub->blockS);
	mlx_resize_image(cub->map.east, cub->blockS, cub->blockS);
	mlx_resize_image(cub->map.west, cub->blockS, cub->blockS);
}

int	prepare_textures(t_cub *cub)
{
	if (!load_texture(cub->mlx, &(cub->map.north), cub->map.no))
		return 0;
	if (!load_texture(cub->mlx, &(cub->map.south), cub->map.so))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		return 0;
	}
	if (!load_texture(cub->mlx, &(cub->map.east), cub->map.ea))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		return 0;
	}
	if (!load_texture(cub->mlx, &(cub->map.west), cub->map.we))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		mlx_delete_image(cub->mlx, cub->map.east);
		return 0;
	}
	//resize_textures(cub);
	return 1;
}
