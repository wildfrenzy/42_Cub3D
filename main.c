/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:36:21 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/18 23:25:52 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};
int mapX = 8;
int mapY = 8;
int blockS = 64;

void	ft_raycast(t_cub *cub)
{
	if ()
}

void	ft_start(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int     exit_status;
	
	exit_status = ft_init_cub(&cub, argc, argv);
	if (exit_status)
		return (ft_clean_exit(exit_status, &cub));
	ft_start(&cub);
	return (exit_status);
}