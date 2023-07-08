/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:15:52 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/08 14:59:54 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clean_exit(int stat, t_cub *cub)
{
	if (stat > 2)
	{
		if (cub->map.east)
			mlx_delete_image(cub->mlx, cub->map.east);
		if (cub->map.west)
			mlx_delete_image(cub->mlx, cub->map.west);
		if (cub->map.north)
			mlx_delete_image(cub->mlx, cub->map.north);
		if (cub->map.south)
			mlx_delete_image(cub->mlx, cub->map.south);
	}
	if (stat > 0 && cub->img)
		mlx_delete_image(cub->mlx, cub->img);
	if (stat == 10)
	{
		if (cub->mlx)
			mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	if (stat >= 0)
		free_map(&cub->map);
	// if (stat > 2)
	exit (stat);
}
