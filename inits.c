/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/06/19 01:18:54 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_map(t_cub *cub)
{
	t_colour	floor;
	t_colour	ceiling;

	floor.r = 0;
	floor.g = 0;
	floor.b = 0;

	ceiling.r = 0;
	ceiling.g = 0;
	ceiling.b = 0;

	cub->map.floor = floor;
	cub->map.ceiling = ceiling;
	cub->map.map = NULL;
	cub->map.no = NULL;
	cub->map.so = NULL;
	cub->map.we = NULL;
	cub->map.ea = NULL;
	cub->map.mapX = 0;
	cub->map.mapY = 0;
	cub->map.all_info = 0;

	return (0);
}

int	ft_init_rays(t_cub *cub)
{
	cub->rays = malloc(sizeof(t_rays));
	if (!cub->rays)
		return (1);
	cub->rays->ray = 0;
	cub->rays->horizontal.colour = ft_rgba_to_int(222, 184, 65, 255);
	cub->rays->vertical.colour = ft_rgba_to_int(222, 158, 54, 255);
	//change colors after parsing them
	return (0);
}

int	ft_init_player(t_cub *cub)
{
	//cub->player.direction = 127;
	cub->player.pos.x = 410; //0
	cub->player.pos.y = 410; //0
	cub->player.dir.angle = 90.0;
	cub->player.dir.delta_x = cos(ft_deg_to_rad(cub->player.dir.angle));
	cub->player.dir.delta_y = -sin(ft_deg_to_rad(cub->player.dir.angle));
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
	if (ft_init_map(cub))
		return (4);
	if (ft_init_player(cub))
		return (5);
	if (ft_init_rays(cub))
		return (5);
	return (0);
}
