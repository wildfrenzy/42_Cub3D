/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:07:04 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/08 11:14:29 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tape_the_wall(t_cub *cub, int x)
{
	double	step;
	double	tex_pos;
	int		y;

	step = 1.0 * cub->chosen_texture->height / cub->line_h;
	tex_pos = (cub->draw_start - cub->mlx->height / 2 + cub->line_h / 2) * step;
	y = cub->draw_start - 1;
	while (++y <= cub->draw_end)
	{
		cub->tex.y = (int)tex_pos ;
		if (cub->tex.y >= cub->chosen_texture->height)
			cub->tex.y = (int)(cub->chosen_texture->height - 1);
		tex_pos += step;
		put_textel(cub->img, x, y, \
				get_color_textel(cub, cub->tex.x, cub->tex.y));
	}
}

void	measure_tape(t_cub *cub)
{
	if (cub->side == 0)
		cub->wall_x = cub->player.pos.y + cub->perp_wall_dist * cub->ray.y;
	else
		cub->wall_x = cub->player.pos.x + cub->perp_wall_dist * cub->ray.x;
	cub->wall_x -= floor(cub->wall_x);
	cub->tex.x = (int)(cub->wall_x * (double)cub->chosen_texture->width);
	if (cub->side == 0 && cub->ray.x > 0)
		cub->tex.x = cub->chosen_texture->width - cub->tex.x - 1;
	if (cub->side == 1 && cub->ray.y < 0)
		cub->tex.x = cub->chosen_texture->width - cub->tex.x - 1;
}

void	this_wall_is_high(t_cub *cub)
{
	if (cub->side == 0)
		cub->perp_wall_dist = cub->side_dist.x - cub->delta_dist.x;
	else
		cub->perp_wall_dist = cub->side_dist.y - cub->delta_dist.y;
	cub->line_h = (int)(cub->mlx->height / cub->perp_wall_dist);
	cub->draw_start = cub->mlx->height / 2 - cub->line_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_h / 2 + cub->mlx->height / 2;
	if (cub->draw_end >= cub->mlx->height)
		cub->draw_end = cub->mlx->height - 1;
}

void	welcome_to_the_dda(t_cub *cub)
{
	while (cub->hit == 0)
	{
		if (cub->side_dist.x < cub->side_dist.y)
		{
			cub->side_dist.x += cub->delta_dist.x;
			cub->map.pos.x += cub->step.x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist.y += cub->delta_dist.y;
			cub->map.pos.y += cub->step.y;
			cub->side = 1;
		}
		if (cub->map.map[cub->map.pos.y * cub->map.map_x + cub->map.pos.x] > 0)
			cub->hit = 1;
	}
}

void	ft_catjam(void *param)
{
	t_cub	*cub;
	double	camera_x;
	int		x;

	cub = param;
	x = -1;
	while (++x < cub->mlx->width)
	{
		camera_x = 2 * x / (double)cub->mlx->width - 1;
		cub->ray.x = cub->player.dir.x + cub->player.plane.x * camera_x;
		cub->ray.y = cub->player.dir.y + cub->player.plane.y * camera_x;
		cub->map.pos.x = (int) cub->player.pos.x;
		cub->map.pos.y = (int) cub->player.pos.y;
		set_delta_dist(cub);
		cub->hit = 0;
		calc_step(cub);
		welcome_to_the_dda(cub);
		this_wall_is_high(cub);
		choose_the_tape(cub);
		measure_tape(cub);
		tape_the_wall(cub, x);
	}
}
