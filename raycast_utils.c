/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:12:44 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/07/09 14:36:16 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color_textel(t_cub *cub, int x, int y)
{
	unsigned int	*color;
	unsigned int	index;

	index = (y * cub->chosen_texture->width + x) * 4;
	color = (unsigned int *) &(cub->chosen_texture->pixels[index]);
	return (*color);
}

void	put_textel(mlx_image_t *img, int x, int y, unsigned int colour)
{
	unsigned int	*pixel;

	if (x < img->width && y < img->height)
	{
		pixel = (unsigned int *)&img->pixels[(x + y * img->width) * 4];
		*pixel = colour;
	}
}

/**
 * Delta is the distance
 * the ray has to travel to go from 1 x-side to the next x-side,
 * or from 1 y-side to the next y-side.
 */

void	set_delta_dist(t_cub *cub)
{
	if (cub->ray.x == 0)
		cub->delta_dist.x = 1e30;
	else
		cub->delta_dist.x = fabs(1 / cub->ray.x);
	if (cub->ray.y == 0)
		cub->delta_dist.y = 1e30;
	else
		cub->delta_dist.y = fabs(1 / cub->ray.y);
}

void	calc_step(t_cub *cub)
{
	if (cub->ray.x < 0)
	{
		cub->step.x = -1;
		cub->side_dist.x = (cub->player.pos.x - cub->map.pos.x) * \
							cub->delta_dist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->side_dist.x = (cub->map.pos.x + 1.0 - cub->player.pos.x) * \
							cub->delta_dist.x;
	}
	if (cub->ray.y < 0)
	{
		cub->step.y = -1;
		cub->side_dist.y = (cub->player.pos.y - cub->map.pos.y) * \
							cub->delta_dist.y;
	}
	else
	{
		cub->step.y = 1;
		cub->side_dist.y = (cub->map.pos.y + 1.0 - cub->player.pos.y) * \
							cub->delta_dist.y;
	}
}

void	choose_the_tape(t_cub *cub)
{
	if (cub->side == 0 && cub->step.x < 0)
		cub->chosen_texture = cub->map.east;
	if (cub->side == 0 && cub->step.x > 0)
		cub->chosen_texture = cub->map.west;
	if (cub->side == 1 && cub->step.y < 0)
		cub->chosen_texture = cub->map.north;
	if (cub->side == 1 && cub->step.y > 0)
		cub->chosen_texture = cub->map.south;
}
