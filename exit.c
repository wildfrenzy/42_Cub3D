/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:15:52 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/08 14:25:45 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clean_exit(int stat, t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	if (stat > 1)
	{
		mlx_delete_image(cub->mlx, cub->map.east);
		mlx_delete_image(cub->mlx, cub->map.west);
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
	}
	mlx_close_window(cub->mlx);
	free_map(&(cub->map));
	exit (stat);
}
