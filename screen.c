/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:29:59 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/30 19:03:46 by bmacmaho         ###   ########.fr       */
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
	cub->rays->shortest->dist *= cos(ft_deg_to_rad(delta_angle));
	line_height = (int)(cub->mlx->height * blockS / cub->rays->shortest->dist);
	if (line_height > cub->mlx->height)
		line_height = cub->mlx->height;
	line_offset = (cub->mlx->height / 2.) - (line_height / 2);
	top.x = cub->rays->ray;
	top.y = line_offset;
	bottom.x = top.x;
	bottom.y = (int)(line_height + line_offset);

	//ft_safe_draw(cub->img, top.x, bottom.y, get_textel(cub));
	new_ft_line(cub->img, top, bottom, get_textel(cub, (int)get_wall_height(cub->rays->shortest->dist)));// cub->rays->shortest->colour); // get texture color and send in ftline.

}
