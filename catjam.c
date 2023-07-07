/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catjam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <nmaliare@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:07:04 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/06 21:07:56 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int get_color_textel(t_cub *cub, int x, int y)
{
	unsigned int *color;

	color = (unsigned int *) &(cub->chosen_texture->pixels[(y * cub->chosen_texture->width + x) * 4]);
	return (*color);
}

void put_textel(mlx_image_t *img, unsigned int x, unsigned int y, unsigned int colour)
{
	unsigned int	*pixel;

	pixel = (unsigned int *)&img->pixels[(x + y * img->width) * sizeof(unsigned int)];
	*pixel = colour;
}

void	tape_the_wall(t_cub *cub, int x)
{
	double	step;
	double	tex_pos;
	int y;

	step = 1.0 * cub->chosen_texture->height / cub->line_h;
	tex_pos = (cub->draw_start - cub->mlx->height / 2 + cub->line_h / 2) * step;
	y = cub->draw_start - 1;
	while (++y <= cub->draw_end)
	{
		// Cast the texture coordinate to integer,
		// and mask with (texHeight - 1) in case of overflow
		cub->tex.y = (int)tex_pos ;
		if (cub->tex.y >= cub->chosen_texture->height )
			cub->tex.y =  (int)(cub->chosen_texture->height - 1);
		tex_pos += step;
		put_textel(cub->img, x, y, get_color_textel(cub, cub->tex.x, cub->tex.y));
	}
}

void	choose_the_tape(t_cub *cub)
{
	// ?  == 0
	if (cub->side == 0 && cub->step.x < 0)
		cub->chosen_texture = cub->map.east;
	if (cub->side == 0 && cub->step.x > 0)
		cub->chosen_texture = cub->map.west;
	if (cub->side == 1 && cub->step.y < 0)
		cub->chosen_texture = cub->map.north;
	if (cub->side == 1 && cub->step.y > 0)
		cub->chosen_texture = cub->map.south;
}

void	measure_tape(t_cub *cub)
{
	//where exactly the wall was hit
	if (cub->side == 0)
		cub->wall_x = cub->player.pos.y + cub->perp_wall_dist * cub->ray.y;
	else
		cub->wall_x = cub->player.pos.x + cub->perp_wall_dist * cub->ray.x;
	cub->wall_x -= floor(cub->wall_x);

	cub->tex.x = (int)(cub->wall_x * (double)cub->chosen_texture->width);
	if ((cub->side == 0 && cub->ray.x > 0) || (cub->side == 1 && cub->ray.y < 0))
		cub->tex.x = cub->chosen_texture->width - cub->tex.x - 1;

}

void	this_wall_is_high(t_cub *cub)
{
	//Calculate distance of perpendicular ray

	if (cub->side == 0)
		cub->perp_wall_dist = cub->side_dist.x - cub->delta_dist.x;
	else
		cub->perp_wall_dist = cub->side_dist.y - cub->delta_dist.y;

	cub->line_h = (int) (cub->mlx->height / cub->perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	cub->draw_start = cub->mlx->height / 2 - cub->line_h / 2;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_h / 2 + cub->mlx->height / 2;
	if (cub->draw_end >= cub->mlx->height)
		cub->draw_end = cub->mlx->height - 1;
}

/**
 * The DDA algorithm will always jump exactly one square each loop,
 * either a square in the x-direction, or a square in the y-direction.
 * If it has to go in the negative or positive x-direction,
 * and the negative or positive y-direction will depend on the direction of the ray,
 * and this fact will be stored in stepX and stepY.
 * Those variables are always either -1 or +1.
 * */

void	welcome_to_the_dda(t_cub *cub)
{
	while (cub->hit == 0)
	{
		if (cub->side_dist.x < cub->side_dist.y)
		{
			cub->side_dist.x += cub->delta_dist.x;
			cub->map.pos.x += cub->step.x;
			cub->side = 0;
		} else
		{
			cub->side_dist.y += cub->delta_dist.y;
			cub->map.pos.y += cub->step.y;
			cub->side = 1;
		}
		if (cub->map.map[cub->map.pos.y * cub->map.mapX + cub->map.pos.x] > 0)
			cub->hit = 1;
	}
}

void	calc_step(t_cub *cub)
{
	if (cub->ray.x < 0)
	{
		cub->step.x = -1;
		cub->side_dist.x = (cub->player.pos.x - cub->map.pos.x) * cub->delta_dist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->side_dist.x = (cub->map.pos.x + 1.0 - cub->player.pos.x ) * cub->delta_dist.x;
	}
	if (cub->ray.y < 0)
	{
		cub->step.y = -1;
		cub->side_dist.y = (cub->player.pos.y - cub->map.pos.y) * cub->delta_dist.y;
	}
	else
	{
		cub->step.y = 1;
		cub->side_dist.y = (cub->map.pos.y + 1.0 - cub->player.pos.y) * cub->delta_dist.y;
	}
}

void	set_delta_dist(t_cub *cub)
{
	//length of ray from one x or y-side to next x or y-side
	if (cub->ray.x == 0)
		cub->delta_dist.x = 1e30;
	else
		cub->delta_dist.x = fabs(1 / cub->ray.x);
	if (cub->ray.y == 0)
		cub->delta_dist.y = 1e30;
	else
		cub->delta_dist.y = fabs(1 / cub->ray.y);
}

// https://www.youtube.com/watch?v=Pb-dJFnFSrc

void ft_catjam(void *param)
{
	t_cub *cub;
	cub = param;

	double cameraX;

	int x = -1;

	//reset window
	while (++x < cub->mlx->width)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)cub->mlx->width - 1;
		cub->ray.x = cub->player.dir.x + cub->player.plane.x * cameraX;
		cub->ray.y = cub->player.dir.y + cub->player.plane.y * cameraX;

		cub->map.pos.x = (int) cub->player.pos.x;
		cub->map.pos.y = (int) cub->player.pos.y;

		set_delta_dist(cub);
		cub->hit = 0;
		calc_step(cub);
		welcome_to_the_dda(cub);

		this_wall_is_high(cub);

		//draw_wall(cub, x, rgba(250,250,0,255));

		choose_the_tape(cub);
		measure_tape(cub);

		tape_the_wall(cub, x);



	}

}