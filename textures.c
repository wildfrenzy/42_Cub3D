/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:41 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/27 20:12:00 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_trytexture(void *param)
{
	t_cub *cub;

	cub = param;

	mlx_image_t *main = cub->img;
	mlx_image_t *texture1 = cub->map.north;
	mlx_image_t *texture2 = cub->map.south;

	/*mlx_resize_image(texture1, 100, 100);
	mlx_resize_image(texture2, 100, 100);*/

	int tx;
	int ty;
	int t_index;

	for (int y = 0; y < cub->mlx->width; y++) {
		for (int x = 0; x < cub->mlx->height; x++) {
			int m_index = (y * main->width + x) * 4;

			if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 184 && main->pixels[m_index + 2] == 65) {

				tx = x % texture1->width;
				ty = y % texture1->height; // y - y_coord where wall starts
				t_index = (ty * texture1->width + tx) * 4;

				main->pixels[m_index] = texture1->pixels[t_index];
				main->pixels[m_index + 1] = texture1->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture1->pixels[t_index + 2];
			}
			else if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 158 && main->pixels[m_index + 2] == 54) {

				tx = x % texture2->width;
				ty = y % texture2->height;
				t_index = (ty * texture2->width + tx) * 4;

				main->pixels[m_index] = texture2->pixels[t_index];
				main->pixels[m_index + 1] = texture2->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture2->pixels[t_index + 2];
			}
		}
	}
}

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
	return 1;
}