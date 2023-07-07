/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:11:23 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/07/07 15:58:37 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ROT 0.042

static void	rightangle(t_delta *dir, char ad)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = M_PI / 2.0;
	if (ad == 'a')
		angle = -M_PI / 2.0;
	old_dir_x = dir->x;
	dir->x = dir->x * cos(angle) - \
		dir->y * sin(angle);
	dir->y = old_dir_x * sin(angle) + dir->y \
		* cos(angle);
}

static void	move(t_cub *cub, char key)
{
	int		newx;
	int		newy;
	double	ws;
	t_delta	dir;
	double	move_speed;

	move_speed = 0.06;
	ws = 1.0;
	dir.x = cub->player.dir.x;
	dir.y = cub->player.dir.y;
	if (key == 'w')
		ws = 1.0;
	if (key == 's')
		ws = -1.0;
	if (key == 'a' || key == 'd')
		rightangle(&dir, key);
	newx = (int)(cub->player.pos.y) * cub->map.mapX + (int)(cub->player.pos.x \
		+ (dir.x * (move_speed + 0.01)) * ws);
	newy = (int)(cub->player.pos.y + (dir.y * \
		(move_speed + 0.01)) * ws) * cub->map.mapX + (int)(cub->player.pos.x);
	if (cub->map.map[newx] == 0)
		cub->player.pos.x += dir.x * move_speed * ws;
	if (cub->map.map[newy] == 0)
		cub->player.pos.y += dir.y * move_speed * ws;
}

void	rotate(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(rot_speed) - \
		cub->player.dir.y * sin(rot_speed);
	cub->player.dir.y = old_dir_x * sin(rot_speed) + cub->player.dir.y \
		* cos(rot_speed);
	old_plane_x = cub->player.plane.x;
	cub->player.plane.x = cub->player.plane.x * cos(rot_speed) - \
		cub->player.plane.y * sin(rot_speed);
	cub->player.plane.y = old_plane_x * sin(rot_speed) + cub->player.plane.y \
		* cos(rot_speed);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		ft_clean_exit(10, cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move(cub, 'w');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move(cub, 's');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move(cub, 'a');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move(cub, 'd');
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate(cub, -ROT);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate(cub, ROT);
}
