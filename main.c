/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:24:55 by barramacmah       #+#    #+#             */
/*   Updated: 2023/06/28 16:19:31 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ww = WIDTH;
int hh = HEIGHT;

void	ft_main_loop(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_background, cub);
	mlx_loop_hook(cub->mlx, ft_2d_grid, cub);
	mlx_loop_hook(cub->mlx, ft_raycast, cub);
	mlx_loop_hook(cub->mlx, ft_draw_player, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		how_long_till_map = 1;

	
	if (ft_errors(argc, argv));
		return (1);
	ft_init_map(&cub);

	if (!gather_data(&(cub.map), argv[1], &how_long_till_map) || !create_int_map(&(cub.map)) ||
		!fill_that_map(&cub, argv[1], how_long_till_map) || !validate_walls(&(cub.map)))
		return free_map(&(cub.map));

	if (ft_init_cub(&cub, argc, argv))
		return (ft_clean_exit(&cub));
	if (!prepare_textures(&cub))
		return free_map(&(cub.map));

	ft_init_player(&cub);
	print_map_data(&cub, how_long_till_map);

	ft_main_loop(&cub);

	free_map(&(cub.map));
	return (0);
}
