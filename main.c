/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:36:21 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/30 19:13:56 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_main_loop(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_background, cub);
	// mlx_loop_hook(cub->mlx, ft_2d_grid, cub);
	// mlx_loop_hook(cub->mlx, ft_draw_player, cub);
	mlx_loop_hook(cub->mlx, ft_raycast, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		exit_status;

	exit_status = ft_init_cub(&cub, argc, argv);
	if (exit_status)
		return (ft_clean_exit(exit_status, &cub));
	ft_main_loop(&cub);
	return (exit_status);
}
