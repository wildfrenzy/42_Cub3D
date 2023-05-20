/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:11:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/20 18:39:49 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	{
		cub->player->position.x += (int) (cub->player->delta_x * 5.0);
		cub->player->position.y += (int) (cub->player->delta_y * 5.0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	{
		cub->player->position.x -= (int) (cub->player->delta_x * 5.0);
		cub->player->position.y -= (int) (cub->player->delta_y * 5.0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player->direction += 5;
		cub->player->direction = ft_fix_angle(cub->player->direction);
		printf("%d\n", cub->player->direction);
		cub->player->delta_x = (float) (cos(ft_deg_to_rad(cub->player->direction)));
		cub->player->delta_y = (float) (-sin(ft_deg_to_rad(cub->player->direction)));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player->direction -= 5;
		cub->player->direction = ft_fix_angle(cub->player->direction);
		printf("%d\n", cub->player->direction);
		cub->player->delta_x = (float) (cos(ft_deg_to_rad(cub->player->direction)));
		cub->player->delta_y = (float) (-sin(ft_deg_to_rad(cub->player->direction)));
	}
}
