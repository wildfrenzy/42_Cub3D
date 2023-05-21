/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/21 23:14:14 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

void	ft_draw_ray(t_cub *cub)
{
	t_point	top_left;
	t_point	bottom_right;
	int		line_height;

	line_height = (blockS * HEIGHT) / cub->rays->shortest->dist;
	if (line_height > HEIGHT)
		line_height = HEIGHT;
	top_left.x = cub->rays->ray * (WIDTH / 60);
	top_left.y = HEIGHT - line_height;
	bottom_right.x = top_left.x + (WIDTH / 60) - 1;
	bottom_right.y = HEIGHT - top_left.y;
	ft_filled_square(cub->img, top_left, bottom_right, \
			cub->rays->shortest->colour);
}
