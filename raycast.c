/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:09:09 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/21 23:24:01 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	map[];
extern int	mapX;
extern int	mapY;
extern int	blockS;

int	ft_is_wall(t_cub *cub, t_point *ray_end)
{
	t_point	cell;
	int		index;

	cell.x = ray_end->x / blockS;
	cell.y = ray_end->y / blockS;
	index = cell.y * mapX + cell.x;
	printf("%d\n", index);
	if (map[index] == 1)
		return (1);
	else
		return (0);
}

int	ft_check_horizontal(t_cub *cub)
{
	int		dist;
	int		o;
	int		angle;
	t_point	*rayend;

	o = ft_h_delta_y(cub, cub->player->pos.y);
	angle = ft_h_angle(cub->rays->ray_angle);
	dist = o / sin(ft_deg_to_rad(angle));
	rayend = &cub->rays->horizontal.end;
	rayend->y = cub->player->pos.y;
	rayend->y += o * cub->rays->up;
	rayend->x = cub->player->pos.x;
	rayend->x = o / tan(ft_deg_to_rad(angle)) * cub->rays->up;
	while (ft_onscreen(rayend) && !(ft_is_wall(cub, rayend)))
	{
		dist += blockS / sin(ft_deg_to_rad(angle));
		rayend->y += blockS * cub->rays->up;
		rayend->x += blockS / tan(ft_deg_to_rad(angle));
	}
	return (dist);
}

int	ft_check_vertical(t_cub *cub)
{
	int		dist;
	int		a;
	int		angle;
	t_point	*rayend;

	a = ft_v_delta_x(cub, cub->player->pos.x);
	angle = ft_v_angle(cub->rays->ray_angle);
	dist = a / cos(ft_deg_to_rad(angle));
	rayend = &cub->rays->vertical.end;
	rayend->x = cub->player->pos.x;
	rayend->x += a * cub->rays->left;
	rayend->y = cub->player->pos.y;
	rayend->y += a * tan(ft_deg_to_rad(angle)) * cub->rays->up;
	while (ft_onscreen(rayend) && !(ft_is_wall(cub, rayend)))
	{
		dist += blockS / (cos(angle));
		rayend->x += blockS * cub->rays->left;
		rayend->y += blockS * tan(angle) * cub->rays->up;
	}
	return (dist);
}

void	ft_ray_quadrant(t_rays *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < 180)
		ray->up = -1;
	else
		ray->up = 1;
	if (ray->ray_angle > 90 && ray->ray_angle < 270)
		ray->left = -1;
	else
		ray->left = 1;
}

void	ft_raycast(void *v_cub)
{
	t_cub	*cub;
	t_rays	*rays;

	cub = v_cub;
	rays = cub->rays;
	rays->ray = -1;
	rays->ray_angle = cub->player->dir.angle - 30;
	while (++rays->ray < 60)
	{
		ft_ray_quadrant(rays);
		rays->vertical.dist = ft_check_vertical(cub);
		rays->horizontal.dist = ft_check_horizontal(cub);
		if (rays->horizontal.dist < rays->vertical.dist)
			rays->shortest = &rays->horizontal;
		else
			rays->shortest = &rays->vertical;
		ft_draw_ray(cub);
		rays->ray_angle++;
	}
}
