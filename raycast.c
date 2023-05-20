/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:09:09 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/21 01:15:57 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	map[];
extern int	mapX;
extern int	mapY;
extern int	blockS;

int	ft_is_wall(t_cub *cub)
{
	t_point	*ray_end;
	t_point	cell;
	int		index;

	ray_end = &cub->rays->ray_end;
	cell.x = ray_end->x / blockS;
	cell.y = ray_end->y / blockS;
	index = cell.y * mapX + cell.x;
	if (map[index] == 1)
		return (1);
	else
		return (0);
}

int	ft_dist_to_next_v_gridline(t_cub *cub)
{
	int	dist;
	int	a;
	int	angle;

	angle = cub->rays->ray_angle;
	if (angle < 90)
		a = blockS - (cub->player->pos.x % blockS);
	else if (angle < 180)
	{
		a = cub->player->pos.x % blockS;
		angle = 180 - angle;
	}
	else if (cub->rays->ray_angle < 270)
	{
		a = cub->player->pos.x % blockS;
		angle = angle - 180;
	}
	else
	{
		a = blockS - (cub->player->pos.x % blockS);
		angle = 360 - angle;
	}
	dist = a / cos(ft_deg_to_rad(angle));
	return (dist);
}

int	ft_dist_to_next_h_gridline(t_cub *cub)
{
	int	a;
	int	angle;

	angle = cub->rays->ray_angle;
	if (angle < 90)
	{
		angle = 90 - angle;
		a = cub->player->pos.y % blockS;
	}
	else if (angle < 180)
	{
		angle = angle - 90;
		a = cub->player->pos.y % blockS;
	}
	else if (cub->rays->ray_angle < 270)
	{
		angle = 270 - angle;
		a = blockS - (cub->player->pos.y % blockS);
	}
	else
	{
		a = blockS - (cub->player->pos.y % blockS);
		angle = angle - 270;
	}
	return (a / cos(ft_deg_to_rad(angle)));
}

// void	ft_raycast(void* v_cub)
// {
// 	t_cub	*cub;
// 	t_rays	*rays;

// 	cub = v_cub;
// 	cub->rays->ray = -1;
// 	rays = cub->rays;
// 	rays->ray_angle = cub->player->dir.angle - 30;
// 	while (++rays->ray < 60)
// 	{
// 		rays->colour = ft_rgba_to_int(200, 0, 0, 255);
// 		rays->v_dist = ft_check_vertical(cub);
// 		rays->h_dist = ft_check_horizontal(cub);
// 		if (rays->h_dist < rays->v_dist)
// 		{
// 			rays->colour = ft_rgba_to_int(255, 0, 0, 255);
// 			rays->dist = rays->h_dist;
// 		}
// 		else
// 			rays->dist = rays->v_dist;
// 	}
// 	exit (0);
// }