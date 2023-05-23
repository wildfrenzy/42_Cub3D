/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/23 23:49:35 by bmacmaho         ###   ########.fr       */
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
	cub->rays->shortest->dist *= cos(ft_deg_to_rad(ft_fix_angle(delta_angle)));
	line_height = (HEIGHT * blockS) / cub->rays->shortest->dist;
	if (line_height > HEIGHT)
		line_height = (float) HEIGHT;
	printf("LH: %3.3f\n", line_height);
	line_offset = (HEIGHT / 2) - ((int)line_height / 2);
	top_left.x = (cub->rays->ray) * (WIDTH / 60);
	top_left.y = line_offset;
	bottom_right.x = top_left.x + ((WIDTH / 60));
	bottom_right.y = (int)(line_height + line_offset);
	ft_filled_square(cub->img, top_left, bottom_right, \
		cub->rays->shortest->colour);
}
