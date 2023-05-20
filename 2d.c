/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:49:36 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/20 18:43:18 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};
int mapX = 8;
int mapY = 8;
int blockS = 64;

void	ft_2d_grid(void *v_cub)
{
	t_cub	*cub;
	t_point	xyo;
	t_point	xyo2;
	t_point	i;
	int		colour;

	cub = v_cub;
	i.y = -1;
	while (++i.y < mapY)
	{
		i.x = -1;
		while (++i.x < mapX)
		{
			if (map[i.y * mapX + i.x] == 1)
				colour = ft_rgba_to_int(255, 255, 255, 255);
			else
				colour = ft_rgba_to_int(0, 0, 0, 255);
			xyo.x = i.x * blockS;
			xyo.y = i.y * blockS;
			xyo2.x = xyo.x + blockS;
			xyo2.y = xyo.y + blockS;
			ft_filled_square(cub->img, xyo, xyo2, colour);
			ft_empty_square(cub->img, xyo, xyo2, ft_rgba_to_int(0, 0, 0, 255));
		}
	}
}

void	ft_draw_player(void *v_cub)
{
	t_cub	*cub;
	t_point	player[2];

	cub = v_cub;
	player[0].x = cub->player->position.x - 4;
	player[0].y = cub->player->position.y - 4;
	player[1].x = cub->player->position.x + 4;
	player[1].y = cub->player->position.y + 4;
	ft_filled_square(cub->img, player[0], player[1], \
			ft_rgba_to_int(255, 0, 0, 255));
	player[0].x = (cub->player->position.x + (int) (cub->player->delta_x * 10.0));
	player[0].y = (cub->player->position.y + (int) (cub->player->delta_y * 10.0));
	printf("delta x, y: %3.3f %3.3f\n", cub->player->delta_x, cub->player->delta_y);
	ft_line(cub->img, cub->player->position, player[0], \
			ft_rgba_to_int(255, 0, 0, 255));
}
