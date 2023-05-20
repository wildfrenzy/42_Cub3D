/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:51:49 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/05/20 16:40:36 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_dir(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

void	ft_line(mlx_image_t *img, t_point p1, t_point p2, int colour)
{
	t_point	delta;
	t_point	dir;
	int		error[2];

	delta.x = abs(p2.x - p1.x);
	delta.y = abs(p2.y - p1.y);
	dir.x = ft_dir(p1.x, p2.x);
	dir.y = ft_dir(p1.y, p2.y);
	error[0] = delta.x - delta.y;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		ft_safe_draw(img, p1.x, p1.y, colour);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
		{
			error[0] -= delta.y;
			p1.x += dir.x;
		}
		if (error[0] < delta.x)
		{
			error[0] += delta.x;
			p1.y += dir.y;
		}
	}
	ft_safe_draw(img, p1.x, p1.y, colour);
}

void	ft_empty_square(mlx_image_t *img, t_point nw, t_point se, int colour)
{
	t_point	ne;
	t_point	sw;

	ne.x = se.x;
	ne.y = nw.y;
	sw.x = nw.x;
	sw.y = se.y;
	ft_line(img, nw, ne, colour);
	ft_line(img, nw, sw, colour);
	ft_line(img, sw, se, colour);
	ft_line(img, ne, se, colour);
}

void	ft_filled_square(mlx_image_t *img, t_point nw, t_point se, int colour)
{
	int		dir;
	t_point	sw;

	sw.x = nw.x;
	sw.y = se.y;
	dir = ft_dir(nw.x, se.x);
	while (nw.x != se.x)
	{
		ft_line(img, nw, sw, colour);
		nw.x += dir;
		sw.x += dir;
	}
	ft_line(img, nw, sw, colour);
}
