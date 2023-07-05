/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/06/24 18:44:56 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int blockS;

int	ft_init_map(t_cub *cub)
{
	t_colour	floor;
	t_colour	ceiling;

	floor.r = 0;
	floor.g = 0;
	floor.b = 0;
	floor.a = 0;

	ceiling.r = 0;
	ceiling.g = 0;
	ceiling.b = 0;
	ceiling.a = 0;

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

/*	cub->map.east = NULL;
	cub->map.west = NULL;
	cub->map.south = NULL;
	cub->map.north = NULL;*/

	return (0);
}

int	ft_init_rays(t_cub *cub)
{
	cub->rays = malloc(sizeof(t_rays));
	if (!cub->rays)
		return (1);
	cub->rays->ray = 0;

	cub->rays->horizontal.colour = ft_rgba_to_int(222, 184, 65, 255); // orange
	cub->rays->vertical.colour = ft_rgba_to_int(222, 158, 54, 255); // yellow

	//cub->rays->is_vertical = false;
	return (0);
}

int	ft_init_player(t_cub *cub)
{
	cub->player.pos.x =  cub->map.pos.x * blockS + blockS/2; //410;
	cub->player.pos.y = cub->map.pos.y * blockS + blockS/2;//410
	if (cub->map.pos.dir == 'E')
		cub->player.dir.angle = 0.0;
	else if (cub->map.pos.dir == 'N')
		cub->player.dir.angle = 90.0;
	else if (cub->map.pos.dir == 'W')
		cub->player.dir.angle = 180.0;
	else if (cub->map.pos.dir == 'S')
		cub->player.dir.angle = 270.0;
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
	/*if (ft_init_map(cub))
		return (4);*/
	/*if (ft_init_player(cub))
		return (5);*/
	if (ft_init_rays(cub))
		return (5);
	return (0);
}
