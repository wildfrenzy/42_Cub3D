/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/25 14:55:24 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

void	ft_draw_ray(t_cub *cub)
{
	t_point	top_left;
	t_point	bottom_right;
	float	line_height;
	float	line_offset;
	int		delta_angle;

	delta_angle = cub->player->dir.angle - cub->rays->ray_angle;
	if (cub->rays->shortest->dist == 0)
		cub->rays->shortest->dist = 1;
	cub->rays->shortest->dist *= cos(ft_deg_to_rad(delta_angle));
	line_height = (int) (HEIGHT * blockS / cub->rays->shortest->dist);
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	line_offset = (HEIGHT / 2) - ((int)line_height / 2);
	top_left.x = (cub->rays->ray) * (WIDTH / 60);
	top_left.y = line_offset;
	bottom_right.x = top_left.x + ((WIDTH / 60));
	bottom_right.y = (int)(line_height + line_offset);
	ft_filled_square(cub->img, top_left, bottom_right, \
		cub->rays->shortest->colour);
}
