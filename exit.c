/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:15:52 by barramacmah       #+#    #+#             */
/*   Updated: 2023/06/26 21:27:44 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clean_exit(int stat, t_cub *cub)
{
	if (stat > 1)
		mlx_close_window(cub->mlx);
//	if (stat > 3)
//		free(cub->player);
	return (stat);
}
