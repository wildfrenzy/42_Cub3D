/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:11:23 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/07/07 12:10:56 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROT 0.042

void	rotate(t_cub *cub, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(rot_speed) - cub->player.dir.y * sin(rot_speed);
	cub->player.dir.y = old_dir_x * sin(rot_speed) + cub->player.dir.y * cos(rot_speed);

	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cos(rot_speed) - cub->player.plane.y * sin(rot_speed);
	cub->player.plane.y = old_plane_x * sin(rot_speed) + cub->player.plane.y * cos(rot_speed);
}

//TODO wasd keys to move. arrows to change view only

void	ft_hook(void *param)
{
	t_cub	*cub;
	double move_speed = 0.06;
	int x_access;
	int y_access;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		ft_clean_exit(10, cub);

	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	{
		x_access =
				(int)(cub->player.pos.y) * cub->map.mapX +
				(int)(cub->player.pos.x + cub->player.dir.x * (move_speed + 0.01));
		y_access =
				(int)(cub->player.pos.y + cub->player.dir.y * (move_speed + 0.01)) *
				cub->map.mapX + (int)(cub->player.pos.x);
		if (cub->map.map[x_access] == 0)
			cub->player.pos.x += cub->player.dir.x * move_speed;
		if (cub->map.map[y_access] == 0)
			cub->player.pos.y += cub->player.dir.y * move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	{
		x_access =
				(int)(cub->player.pos.y) * cub->map.mapX +
				(int)(cub->player.pos.x - cub->player.dir.x * (move_speed + 0.01));
		y_access =
				(int)(cub->player.pos.y - cub->player.dir.y * (move_speed + 0.01)) *
				cub->map.mapX + (int)(cub->player.pos.x);
		if (cub->map.map[x_access] == 0)
			cub->player.pos.x -= cub->player.dir.x * move_speed;
		if (cub->map.map[y_access] == 0)
			cub->player.pos.y -= cub->player.dir.y * move_speed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate(cub, -ROT);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate(cub, ROT);
}
