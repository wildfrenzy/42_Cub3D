/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:36:21 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/08 13:18:59 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recised(void *param)
{
	t_cub	*cub;

	cub = param;
	if (cub->mlx->width != cub->img->width && \
		cub->mlx->height != cub->img->height)
		mlx_resize_image(cub->img, cub->mlx->width, cub->mlx->height);
	else
	{
		if (cub->mlx->width != cub->img->width)
			mlx_resize_image(cub->img, cub->mlx->width, cub->img->height);
		if (cub->mlx->height != cub->img->height)
			mlx_resize_image(cub->img, cub->img->width, cub->mlx->height);
	}
}

void	ft_main_loop(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, ft_background, cub);
	mlx_loop_hook(cub->mlx, ft_catjam, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop_hook(cub->mlx, recised, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		how_long_till_map;

	how_long_till_map = 1;
	if (ft_checkargs(argc, argv))
		return (1);
	if (ft_map(&cub, argv[1], &how_long_till_map))
		return (1);
	if (ft_init_cub(&cub, argc, argv))
		return (ft_clean_exit(1, &cub));
	if (!prepare_textures(&cub))
		return (free_map(&(cub.map)));
	ft_init_player(&cub);
	ft_main_loop(&cub);
	free_map(&(cub.map));
	return (0);
}
