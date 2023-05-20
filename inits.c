/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/21 00:38:03 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_map(t_cub *cub, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	(void) cub;
	return (0);
}

int	ft_init_rays(t_cub *cub)
{
	cub->rays = malloc(sizeof(t_rays));
	if (!cub->rays)
		return (1);
	cub->rays->ray = 0;
	return (0);
}

int	ft_init_player(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->pos.x = 447;
	cub->player->pos.y = 447;
	cub->player->dir.angle = 90;
	cub->player->dir.delta_x = cos(ft_deg_to_rad(cub->player->dir.angle));
	cub->player->dir.delta_y = -sin(ft_deg_to_rad(cub->player->dir.angle));
	return (0);
}

int	ft_init_cub(t_cub *cub, int argc, char **argv)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (2);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (3);
	if (ft_init_map(cub, argc, argv))
		return (4);
	if (ft_init_player(cub))
		return (5);
	if (ft_init_rays(cub))
		return (5);
	return (0);
}
