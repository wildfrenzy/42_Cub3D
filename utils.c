/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:26:11 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/21 00:37:41 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_fix_angle(int deg)
{
	if (deg < 0)
		deg += 360;
	if (deg > 359)
		deg -= 360;
	return (deg);
}

void	ft_safe_draw(mlx_image_t *img, int x, int y, int colour)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(img, x, y, colour);
}

int	ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	ft_deg_to_rad(int degrees)
{
	return (degrees * (PI / 180.0));
}
