/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:15:52 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/08 13:36:34 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clean_exit(int stat, t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	mlx_close_window(cub->mlx);
	free_map(&(cub->map));
	exit (stat);
}
