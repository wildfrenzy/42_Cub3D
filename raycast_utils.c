/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:28:46 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/21 21:11:24 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int	blockS;

int	ft_h_angle(int angle)
{
	if (angle < 90)
		return (90 - angle);
	if (angle < 180)
		return (angle - 90);
	if (angle < 270)
		return (270 - angle);
	return (angle - 270);
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
		return (blockS - (x % blockS));
	return (x % blockS);
}

int	ft_h_delta_y(t_cub *cub, int y)
{
	if (cub->rays->up == -1)
		return (y % blockS);
	return (blockS - (y % blockS));
}
