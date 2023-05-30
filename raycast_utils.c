/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:28:46 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/30 19:14:49 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

double	ft_corresponding_angle(double angle)
{
	if (angle < 90)
		return (angle);
	if (angle < 180)
		return (180 - angle);
	if (angle < 270)
		return (angle - 180);
	return (360 - angle);
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
