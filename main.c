/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:50:27 by nmaliare          #+#    #+#             */
/*   Updated: 2023/05/12 19:32:49 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_draw_player(void* param)
{
	t_cub* cub = param;
	
	for (int32_t i = 0; i < (int)cub->img->width; ++i)
	{
		for (int32_t y = 0; y < (int)cub->img->height; ++y)
		{
			mlx_put_pixel(cub->img, i, y, cub->player->colour);
		}
	}
}

void ft_hook(void* param)
{
	t_cub* cub = param;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		cub->img->instances[0].y -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		cub->img->instances[0].y += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->img->instances[0].x -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->img->instances[0].x += 5;
}

int		ft_init_cub(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->x_pos = 50;
	cub->player->y_pos = 50;
	cub->player->colour = ft_pixel(255,0,0,255);
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(cub->img = mlx_new_image(cub->mlx, 8, 8)))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->img, cub->player->x_pos, cub->player->y_pos) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (0);
}

int32_t main(int32_t argc, const char* argv[])
{
	t_cub	cub;
	(void)argc;(void)argv;

	if (ft_init_cub(&cub))
		return (1);

	mlx_loop_hook(cub.mlx, ft_draw_player, &cub);
	mlx_loop_hook(cub.mlx, ft_hook, &cub);

	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}
