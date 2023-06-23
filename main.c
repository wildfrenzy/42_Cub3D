/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:45:10 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/21 13:36:29 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	print_map_data(t_cub *cub, int how_long_till_map)
{
	printf("\nAll info: %d\nTill map: %d\n", cub->map.all_info, how_long_till_map);
	printf("\ttextures:\n NO:%s\n SO:%s\n WE:%s\n EA:%s\n",
		   cub->map.no, cub->map.so, cub->map.we, cub->map.ea);
	printf("\tcolors:\n F:%d,%d,%d C:%d,%d,%d\n",
		   cub->map.floor.r, cub->map.floor.g, cub->map.floor.b, cub->map.ceiling.r, cub->map.ceiling.g, cub->map.ceiling.b);
	printf("mapX: %d mapY: %d\n\n", cub->map.mapX, cub->map.mapY);
	printf("player: x[%d], y[%d], direction[%c]\n", cub->player.pos.x, cub->player.pos.y, cub->map.pos.dir);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		exit_status;
	int		how_long_till_map = 1;

	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n") & 0);
	if (!check_file(argv[1]))
		return (0);

	ft_init_map(&cub);

	if (!gather_data(&(cub.map), argv[1], &how_long_till_map) || !create_int_map(&(cub.map)) ||
		!fill_that_map(&cub, argv[1], how_long_till_map) || !validate_walls(&(cub.map)))
		return free_map(&(cub.map));

	exit_status = ft_init_cub(&cub);
	if (exit_status)
		return (ft_clean_exit(exit_status, &cub));

	ft_init_player(&cub);
	print_map_data(&cub, how_long_till_map);

	ft_main_loop(&cub);

	free_map(&(cub.map));
	return (exit_status);
}
