/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/20 16:52:36 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_init_map(t_cub *cub, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	(void) cub;
	return (0);
}

int	ft_init_player(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->position.x = 100;
	cub->player->position.y = 100;
	cub->player->direction = 90;
	return (0);
}

int	ft_init_cub(t_cub *cub, int argc, char **argv)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (2);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (3);
	if (ft_init_map(cub, argc, argv))
		return (4);
	if (ft_init_player(cub))
		return (5);
	return (0);
}
