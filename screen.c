/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/24 15:14:34 by bmacmaho         ###   ########.fr       */
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
	printf("1\n");
	printf("DIST: %d\n", cub->rays->shortest->dist);
	if (cub->rays->shortest->dist == 0)
		cub->rays->shortest->dist = 1;
	cub->rays->shortest->dist *= cos(ft_deg_to_rad(delta_angle));
	printf("2 %d\n", cub->rays->shortest->dist);
	line_height = (int) (HEIGHT * blockS / cub->rays->shortest->dist);
	printf("3\n");
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	line_offset = (HEIGHT / 2) - ((int)line_height / 2);
	printf("4\n");
	top_left.x = (cub->rays->ray) * (WIDTH / 60);
	printf("5\n");
	top_left.y = line_offset;
	bottom_right.x = top_left.x + ((WIDTH / 60));
	printf("6\n");
	bottom_right.y = (int)(line_height + line_offset);
	printf("7\n");
	ft_filled_square(cub->img, top_left, bottom_right, \
		cub->rays->shortest->colour);
	printf("8\n");
}
