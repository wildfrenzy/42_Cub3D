/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:36:21 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/23 23:39:57 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_background(void *v_cub)
{
	t_cub	*cub;
	t_point	top_left;
	t_point	bottom_right;

	cub = v_cub;
	top_left.x = 0;
	top_left.y = 0;
	bottom_right.x = WIDTH - 1;
	bottom_right.y = HEIGHT / 2;
	ft_filled_square(cub->img, top_left, bottom_right, \
		ft_rgba_to_int(191, 189, 193, 255));
	top_left.x = 0;
	top_left.y = HEIGHT / 2;
	bottom_right.x = WIDTH - 1;
	bottom_right.y = HEIGHT - 1;
	ft_filled_square(cub->img, top_left, bottom_right, \
		ft_rgba_to_int(55, 50, 62, 255));
}

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
