/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:45:43 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/18 18:48:17 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_start(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_draw_background, cub);
	printf("%d\n", cub->player->angle);
	mlx_loop_hook(cub->mlx, ft_draw_walls, cub);
	printf("%d\n", cub->player->angle);
	mlx_loop_hook(cub->mlx, ft_draw_player, cub);
	printf("%d\n", cub->player->angle);
	mlx_loop_hook(cub->mlx, ft_draw_rays, cub);
	// mlx_loop_hook(cub->mlx, ft_draw_3d, &cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}