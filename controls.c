/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:11:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/18 23:11:45 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	// {
	// 	cub->player->y_pos += cub->player->delta_y * 5;
	// 	cub->player->x_pos += cub->player->delta_x * 5;
	// }
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	// {
	// 	cub->player->y_pos -= cub->player->delta_y * 5;
	// 	cub->player->x_pos -= cub->player->delta_x * 5;
	// }
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	// {
	// 	cub->player->angle += 5;
	// 	cub->player->angle = fix_angle(cub->player->angle);
	// 	cub->player->delta_x = cos(degrees_to_radians(cub->player->angle));
	// 	cub->player->delta_y = -sin(degrees_to_radians(cub->player->angle));
	// }
	// if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	// {
	// 	cub->player->angle -= 5;
	// 	cub->player->angle = fix_angle(cub->player->angle);
	// 	cub->player->delta_x = cos(degrees_to_radians(cub->player->angle));
	// 	cub->player->delta_y = -sin(degrees_to_radians(cub->player->angle));
	// }
}
