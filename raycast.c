/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:09:09 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/24 15:13:49 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

extern int	map[];
extern int	mapX;
extern int	mapY;
extern int	blockS;

int	ft_is_wall(t_cub *cub, t_point *ray_end)
{
	t_point	cell;
	int		index;

	cell.x = (ray_end->x + cub->rays->left) / blockS;
	cell.y = (ray_end->y + cub->rays->up) / blockS;
	index = cell.y * mapX + cell.x;
	if (map[index] == 1)
		return (1);
	else
		return (0);
}

int	ft_check_horizontal(t_cub *cub)
{
	int		dist;
	int		o;
	int		a;
	int		angle;
	t_point	*rayend;

	if (cub->rays->ray_angle == 0 || cub->rays->ray_angle == 360 \
		|| cub->rays->ray_angle == 180)
		return (INT_MAX);
	o = ft_h_delta_y(cub, cub->player->pos.y);
	angle = ft_h_angle(cub->rays->ray_angle);
	dist = ((int)(((float) o) / sin(ft_deg_to_rad(angle))));
	rayend = &cub->rays->horizontal.end;
	rayend->y = cub->player->pos.y;
	rayend->y += o * cub->rays->up;
	rayend->x = cub->player->pos.x;
	a = (int)(((float) o) / tan(ft_deg_to_rad(angle)));
	rayend->x += a * cub->rays->left;
	if (cub->rays->left == -1 && a > cub->player->pos.x)
		return (INT_MAX);
	if (cub->rays->left == 1 && a > (blockS * mapX) - cub->player->pos.x)
		return (INT_MAX);
	while (ft_onscreen(rayend) && !ft_is_wall(cub, rayend))
	{
		dist += (int)(((float) blockS) / sin(ft_deg_to_rad(angle)));
		rayend->y += blockS * cub->rays->up;
		rayend->x += ((int)(((float) blockS) / tan(ft_deg_to_rad(angle)))) \
			* cub->rays->left;
	}
	return (dist);
}

int	ft_check_vertical(t_cub *cub)
{
	int		dist;
	int		a;
	int		o;
	int		angle;
	t_point	*rayend;

	if (cub->rays->ray_angle == 90 || cub->rays->ray_angle == 270)
		return (INT_MAX);
	a = ft_v_delta_x(cub, cub->player->pos.x);
	angle = ft_v_angle(cub->rays->ray_angle);
	dist = (int)(((float) a) / cos(ft_deg_to_rad(angle)));
	rayend = &cub->rays->vertical.end;
	rayend->x = cub->player->pos.x;
	rayend->x += a * cub->rays->left;
	rayend->y = cub->player->pos.y;
	o = (int)(((float) a) * tan(ft_deg_to_rad(angle)));
	rayend->y += o * cub->rays->up;
	if (cub->rays->up == -1 && o > cub->player->pos.y)
		return (INT_MAX);
	if (cub->rays->up == 1 && o > (blockS * mapY) - cub->player->pos.y)
		return (INT_MAX);
	while (ft_onscreen(rayend) && !ft_is_wall(cub, rayend))
	{
		dist += (int)(((float) blockS) / (cos(ft_deg_to_rad(angle))));
		rayend->x += blockS * cub->rays->left;
		rayend->y += (((int)((float) blockS)) * tan(ft_deg_to_rad(angle))) \
			* cub->rays->up;
	}
	return (dist);
}

void	ft_ray_quadrant(t_cub *cub)
{
	t_rays	*ray;

	ray = cub->rays;
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
	rays->ray_angle = ft_fix_angle(cub->player->dir.angle + 30);
	while (++rays->ray < 61)
	{
		ft_ray_quadrant(cub);
		rays->vertical.dist = ft_check_vertical(cub);
		rays->horizontal.dist = ft_check_horizontal(cub);
		if (rays->horizontal.dist < rays->vertical.dist \
			&& rays->horizontal.dist > 0)
			rays->shortest = &rays->horizontal;
		else
			rays->shortest = &rays->vertical;
		ft_line(cub->img, cub->player->pos, rays->shortest->end, \
			rays->shortest->colour);
		ft_draw_ray(cub);
		rays->ray_angle = ft_fix_angle(rays->ray_angle - 1);
	}
}
