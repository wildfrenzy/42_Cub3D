/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:36:21 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/20 16:56:13 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int map[] = {
// 	1,1,1,1,1,1,1,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,
// };
// int mapX = 8;
// int mapY = 8;
// int blockS = 64;

// void	ft_raycast(t_cub *cub)
// {
// 	if ()
// }

// void	ft_2d_grid(void *v_cub)
// {
// 	t_cub *cub;

// 	cub = v_cub;
// 	{
// 	}
// }

void	ft_main_loop(t_cub *cub)
{
	// mlx_loop_hook(cub->mlx, ft_2d_grid, cub);
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
