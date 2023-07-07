/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/07 16:55:34 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_nullfloorceiling(t_colour *floor, t_colour *ceiling)
{
	floor->r = 0;
	floor->g = 0;
	floor->b = 0;
	floor->a = 0;
	ceiling->r = 0;
	ceiling->g = 0;
	ceiling->b = 0;
	ceiling->a = 0;
}

int	ft_init_map(t_cub *cub)
{
	t_colour	floor;
	t_colour	ceiling;

	ft_nullfloorceiling(&floor, &ceiling);
	cub->map.floor = floor;
	cub->map.ceiling = ceiling;
	cub->map.map = NULL;
	cub->map.no = NULL;
	cub->map.so = NULL;
	cub->map.we = NULL;
	cub->map.ea = NULL;
	cub->map.mapX = 0;
	cub->map.mapY = 0;
	cub->map.mapsize = 0;
	cub->map.all_info = 0;
	cub->map.pos.y = 0;
	cub->map.pos.x = 0;
	cub->map.pos.dir = 127;
	cub->blockS = 64;
	return (0);
}

int	ft_init_player(t_cub *cub)
{
	cub->player.pos.x = cub->map.pos.x + 0.5;
	cub->player.pos.y = cub->map.pos.y + 0.5;
	cub->player.plane.x = 0.0;
	cub->player.plane.y = 0.66;
	cub->player.dir.x = 1;
	cub->player.dir.y = 0;
	if (cub->map.pos.dir == 'N')
		rotate(cub, M_PI * 1.5);
	else if (cub->map.pos.dir == 'W')
		rotate(cub, M_PI);
	else if (cub->map.pos.dir == 'S')
		rotate(cub, M_PI / 2);
	return (0);
}

int	ft_init_cub(t_cub *cub, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (2);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (3);
	return (0);
}
