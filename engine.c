/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:45:43 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/16 17:46:30 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_start(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_draw_background, cub);
	mlx_loop_hook(cub->mlx, ft_draw_walls, cub);
	mlx_loop_hook(cub->mlx, ft_draw_player, cub);
	mlx_loop_hook(cub->mlx, ft_draw_rays, cub);
	// mlx_loop_hook(cub->mlx, ft_draw_3d, &cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}