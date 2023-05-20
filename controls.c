/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:11:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/21 00:39:34 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		ft_clean_exit(10, cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	{
		cub->player->pos.x += (int)(cub->player->dir.delta_x * 5.0);
		cub->player->pos.y += (int)(cub->player->dir.delta_y * 5.0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	{
		cub->player->pos.x -= (int)(cub->player->dir.delta_x * 5.0);
		cub->player->pos.y -= (int)(cub->player->dir.delta_y * 5.0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player->dir.angle = ft_fix_angle(cub->player->dir.angle + 5);
		cub->player->dir.delta_x = cos(ft_deg_to_rad(cub->player->dir.angle));
		cub->player->dir.delta_y = -sin(ft_deg_to_rad(cub->player->dir.angle));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player->dir.angle = ft_fix_angle(cub->player->dir.angle - 5);
		cub->player->dir.delta_x = cos(ft_deg_to_rad(cub->player->dir.angle));
		cub->player->dir.delta_y = -sin(ft_deg_to_rad(cub->player->dir.angle));
	}
}
