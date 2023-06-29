/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:41 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/28 21:41:17 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall(int x, int y, t_cub *cub, int *wall_x, int *wall_y)
{
	int m_index;

	// checking 1 previous pixel was ceiling or not;
	if (y > 0)
	{
		m_index = ((y - 1) * cub->img->width + x) * 4;
		if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 184 && cub->img->pixels[m_index + 2] == 65))
			*wall_y = y;
		else if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 158 && cub->img->pixels[m_index + 2] == 54))
			*wall_y = y;
	}
	if (x > 0)
	{
		m_index = (y * cub->img->width + x - 1) * 4;
		if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 184 && cub->img->pixels[m_index + 2] == 65))
			*wall_x = x;
		else if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 158 && cub->img->pixels[m_index + 2] == 54))
			*wall_x = x;
	}
}

void ft_trytexture(void *param)
{
	t_cub *cub;

	cub = param;

	mlx_image_t *main = cub->img;
	mlx_image_t *texture1 = cub->map.north;
	mlx_image_t *texture2 = cub->map.south;

	mlx_resize_image(texture1, 200, 200);
	mlx_resize_image(texture2, 200, 200);

	int tx;
	int ty;
	int t_index;
	int m_index;

	int wall_y = 0;
	int wall_x = 0;

	int stop = 3;

	//printf("mlx_wh[%d][%d] main_wh[%d][%d]\n", cub->mlx->width,cub->mlx->height, main->width, main->height);
	for (int y = 0; y < cub->mlx->height; y++) {
		for (int x = 0; x < cub->mlx->width; x++) {
			if (x > main->width || y > main->height)
			{
				printf("You've gone too far [impossible. almost]\n");
				return ;
			}
			m_index = (y * main->width + x) * 4;

			// orange wall - one texture
			if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 184 && main->pixels[m_index + 2] == 65) {

				check_wall(x, y, cub, &wall_x, &wall_y);

				//printf("w_x[%d] w_y [%d]\n", wall_x, wall_y);

				tx = (x - wall_x) % texture1->width;
				ty = (y - wall_y) % texture1->height; // y - y_coord where wall starts
				t_index = (ty * texture1->width + tx) * 4;

				main->pixels[m_index] = texture1->pixels[t_index];
				main->pixels[m_index + 1] = texture1->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture1->pixels[t_index + 2];
			}
			// yellow wall - another texture
			else if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 158 && main->pixels[m_index + 2] == 54) {

				check_wall(x, y, cub, &wall_x, &wall_y);

				tx = (x - wall_x) % texture2->width;
				ty = (y - wall_y) % texture2->height;
				t_index = (ty * texture2->width + tx) * 4;

				main->pixels[m_index] = texture2->pixels[t_index];
				main->pixels[m_index + 1] = texture2->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture2->pixels[t_index + 2];
			}
		}
		/*printf("y [%d]\n", y);
		stop--;
		if (stop == 0)
			return;*/

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