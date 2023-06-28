/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:28:46 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/06/28 13:32:53 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

double	ft_corresponding_angle(double angle)
{
	if (angle < (M_PI / 2.0))
		return (angle);
	if (angle < M_PI)
		return (M_PI - angle);
	if (angle < (3.0 * M_PI) / 2.0)
		return (angle - M_PI);
	return ((2.0 * M_PI) - angle);
}

double	ft_blocksize_remainder(t_cub *cub, int xy, char hv)
{
	if (hv == 'h')
	{
		if (cub->rays->up == -1)
			return (xy % blockS);
		return (blockS - (xy % blockS));
	}
	if (cub->rays->left == -1)
		return (xy % blockS);
	return (blockS - (xy % blockS));
}
