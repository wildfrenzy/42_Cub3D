/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:45:04 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/15 13:53:09 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_linevars
{
	t_pixel	delta;
	t_pixel	sign;
	int		error[2];
}				t_linevars;

void	ft_init_line(t_pixel *delta, t_pixel *p1, t_pixel *p2, t_pixel *sign)
{
	delta->x = abs(p2->x - p1->x);
	delta->y = abs(p2->y - p1->y);
	if (p1->x < p2->x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p1->y < p2->y)
		sign->y = 1;
	else
		sign->y = -1;
}

void	ft_line(mlx_image_t *img, t_pixel *p1, t_pixel *p2, int colour)
{
	t_linevars	vars;
	t_pixel		cur;

	ft_init_line(&vars.delta, p1, p2, &vars.sign);
	vars.error[0] = vars.delta.x - vars.delta.y;
	cur = *p1;
	while (cur.x != p2->x || cur.y != p2->y)
	{
		if (cur.x >= 0 && cur.x < WIDTH && cur.y >= 0 && cur.y < HEIGHT)
			mlx_put_pixel(img, cur.x, cur.y, colour);
		vars.error[1] = vars.error[0] * 2;
		if (vars.error[1] > -vars.delta.y)
		{
			vars.error[0] -= vars.delta.y;
			cur.x += vars.sign.x;
		}
		if (vars.error[1] < vars.delta.x)
		{
			vars.error[0] += vars.delta.x;
			cur.y += vars.sign.y;
		}
	}
	if (cur.x >= 0 && cur.x < WIDTH && cur.y >= 0 && cur.y < HEIGHT)
		if (cur.x == p2->x || cur.y == p2->y)
			mlx_put_pixel(img, cur.x, cur.y, colour);
}