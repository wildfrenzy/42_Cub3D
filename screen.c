/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/06/28 13:30:50 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

void	ft_draw_ray(t_cub *cub)
{
	t_point	top;
	t_point	bottom;
	double	line_height;
	double	line_offset;
	double	delta_angle;

	delta_angle = cub->player.dir.angle - cub->rays->ray_angle;
	if (cub->rays->shortest->dist == 0.0)
		cub->rays->shortest->dist = 1.0;
	cub->rays->shortest->dist *= cos(delta_angle);
	line_height = (int)(cub->mlx->height * blockS / cub->rays->shortest->dist);
	if (line_height > cub->mlx->height)
		line_height = cub->mlx->height;
	line_offset = (cub->mlx->height / 2) - ((int)line_height / 2);
	top.x = cub->rays->ray;
	top.y = line_offset;
	bottom.x = top.x;
	bottom.y = (int)(line_height + line_offset);
	ft_line(cub->img, top, bottom, cub->rays->shortest->colour);
}
