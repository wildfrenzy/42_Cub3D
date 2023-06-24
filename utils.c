/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:26:11 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/30 19:31:09 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int ww;
extern int hh;

double	ft_fix_angle(double deg)
{
	if (deg < 0.0)
		deg += 360.0;
	if (deg > 359.9)
		deg -= 360.0;
	return (deg);
}

int	ft_onscreen(t_dpoint	*pixel)
{
	if (pixel->x < 0 || pixel->x >= ww)
		return (0);
	if (pixel->y < 0 || pixel->y >= hh)
		return (0);
	return (1);
}

void	ft_safe_draw(mlx_image_t *img, int x, int y, int colour)
{
	if (x >= 0 && x < ww && y >= 0 && y < hh)
		mlx_put_pixel(img, x, y, colour);
}

int	ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	ft_deg_to_rad(double degrees)
{
	return (degrees * (PI / 180.0));
}
