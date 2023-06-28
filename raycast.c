/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:09:09 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/06/28 16:16:06 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

extern int	blockS;

double	ft_distance_between_2_points(t_point p1, t_dpoint *p2)
{
	return (sqrt(pow(p2->x - p1.x, 2) + pow(p2->y - p1.y, 2)));
}

int	ft_is_wall(t_cub *cub, t_dpoint *ray_end)
{
	t_point	cell;
	int		index;

	cell.x = (int) (ray_end->x + (double) cub->rays->left) / blockS;
	cell.y = (int) (ray_end->y + (double) cub->rays->up) / blockS;
	index = cell.y * cub->map.mapX + cell.x;
	//printf("index[%d] of %d\n", index, cub->map.mapX * cub->map.mapY);

	if (index < cub->map.mapsize && cub->map.map[index] == 1)
		return (1);
	else
		return (0);
}

void	ft_findwall(t_cub *cub, double *offset, char vh)
{
	if (vh == 'h')
	{
		while (!ft_is_wall(cub, cub->rays.horizontal.end))
		{
			cub->rays.horizontal.end.x += offset[0];
			cub->rays.horizontal.end.y += offset[1];
		}
	}
	else
	{
		while (!ft_is_wall(cub, &cub->rays.vertical.end))
		{
			cub->rays.vertical.end.x += offset[0];
			cub->rays.vertical.end.y += offset[1];
		}
	}
}

double	ft_check_horizontal(t_cub *cub)
{
	double	tanH;
	double	offset[2];

	tanH = -1 / tan(cub->rays->ray_angle);
	if (cub->rays->ray_angle < (double)M_PI && cub->rays->ray_angle > 0)
	{
		cub->rays->horizontal.end.y = cub->player.pos.y / blockS * blockS + blockS;
		cub->rays->horizontal.end.x = cub->player.pos.x;
		offset[1] = blockS;
	}
	else if (cub->rays->ray_angle > (double)M_PI && cub->rays->ray_angle != (double)M_PI * 2)
	{
		cub->rays->horizontal.end.y = cub->player.pos.y / blockS * blockS - 0.0001f;
		cub->rays->horizontal.end.x = (cub->player.pos.y - cub->rays->horizontal.end.y) * tanH + cub->player.pos.x;
	}
	if (cub->rays->ray_angle == 0 || cub->rays->ray_angle == (double)M_PI)
	{
		cub->rays->horizontal.end.x = cub->player.pos.x;
		cub->rays->horizontal.end.y = cub->player.pos.y;
		return (__DBL_MAX__);
	}
	offset[0] = -offset[1] * tanH;
	ft_findwall(cub, offset, 'h');
	return (sqrt(pow((cub->rays->horizontal.end.x - cub->player.pos.x), 2) + pow((cub->rays->horizontal.end.y - cub->player.pos.y), 2)));
}

double	ft_check_vertical(t_cub *cub)
{
	double	tanV;
	double	offset[2];

	tanV = -tan(cub->rays->ray_angle);
	if (cub->rays->ray_angle > (double)(M_PI_2) && cub->rays->ray_angle < (3 * (double)M_PI_2))
	{
		cub->rays->vertical.end.x = cub->player.pos.x / blockS * blockS - 0.0001f;
		offset[0] = -blockS;
	}
	else if (cub->rays->ray_angle < (double)M_PI_2 || cub->rays->ray_angle > (3 * (double)M_PI_2))
	{
		cub->rays->vertical.end.x = cub->player.pos.x / blockS * blockS + 32;
		offset[0] = blockS;
	}
	cub->rays->vertical.end.y = (cub->player.pos.x - cub->rays->vertical.end.x) * tanV + cub->player.pos.y;
	if (cub->rays->ray_angle == (double)M_PI_2 || cub->rays->ray_angle == (3 * (double)M_PI_2))
	{
		cub->rays->vertical.end.x = cub->player.pos.x;
		cub->rays->vertical.end.y = cub->player.pos.y;
		return (__DBL_MAX__);
	}
	offset[1] = -offset[0] * tanV;
	ft_findwall(cub, offset, 'v');
	return (sqrt(pow((cub->rays->vertical.end.x - cub->player.pos.x), 2) + pow((cub->rays->vertical.end.y - cub->player.pos.y), 2)));
}

void	ft_raycast(void *v_cub)
{
	t_cub	*cub;
	t_rays	*rays;

	cub = v_cub;
	rays = &cub->rays;
	rays->ray = -1;
	rays->ray_angle = ft_fix_angle(cub->player.angle + (M_PI / 6.0));
	while (++rays->ray < cub->mlx->width)
	{
		rays->vertical.dist = ft_check_vertical(cub);
		rays->horizontal.dist = ft_check_horizontal(cub);
		if (rays->horizontal.dist < rays->vertical.dist \
			&& rays->horizontal.dist > 0.0)
			rays->shortest = &rays->horizontal;
		else
			rays->shortest = &rays->vertical;
		ft_line(cub->img, cub->player.pos, &rays->shortest->end, \
			rays->shortest->colour);
		// ft_draw_ray(cub);
		rays->ray_angle = ft_fix_angle(rays->ray_angle - (1.0 * (60.0 / cub->mlx->width)));
	}
}
