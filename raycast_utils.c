/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:28:46 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/24 15:51:58 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

float	ft_hv_angle(float angle)
{
	if (angle < 90.0)
		return (angle);
	if (angle < 180.0)
		return (180.0 - angle);
	if (angle < 270.0)
		return (angle - 180.0);
	return (360.0 - angle);
}

int	ft_v_delta_x(t_cub *cub, int x)
{
	if (cub->rays->left == -1)
		return (x % blockS);
	return (blockS - (x % blockS));
}

int	ft_h_delta_y(t_cub *cub, int y)
{
	if (cub->rays->up == -1)
		return (y % blockS);
	return (blockS - (y % blockS));
}
