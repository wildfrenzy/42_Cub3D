/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:28:46 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/23 20:16:59 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

int	ft_h_angle(int angle)
{
	if (angle < 90)
		return (angle);
	if (angle < 180)
		return (180 - angle);
	if (angle < 270)
		return (angle - 180);
	return (360 - angle);
}

int	ft_v_angle(int angle)
{
	if (angle < 90)
		return (angle);
	if (angle < 180)
		return (180 - angle);
	if (angle < 270)
		return (angle - 180);
	return (360 - angle);
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
