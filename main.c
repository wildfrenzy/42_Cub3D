/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:50:27 by nmaliare          #+#    #+#             */
/*   Updated: 2023/05/15 14:46:10 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[] = {
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};
int	mapX = 8;
int mapY = 8;
int mapS = 64;

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_draw_box(t_pixel xyo, int32_t colour, t_cub *cub)
{
	t_pixel corners[4];
	int i;

	corners[0].x = xyo.x + 1;
	corners[0].y = xyo.y + 1;
	corners[1].x = xyo.x + 1;
	corners[1].y = xyo.y + mapS - 1;
	corners[2].x = xyo.x + mapS - 1;
	corners[2].y = xyo.y + mapS - 1;
	corners[3].x = xyo.x + mapS - 1;
	corners[3].y = xyo.y + 1;
	i = -1;
	while(corners[0].y <= corners[1].y)
	{
		ft_line(cub->img, &corners[0], &corners[3], colour);
		corners[0].y++;
		corners[3].y++;
	}
}

void	ft_draw_walls(void *param)
{
	t_cub *cub;
	t_pixel xyo;
	cub = param;
	int32_t col;
	
	for (int y= 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			if(map[y*mapX+x] == 1)
				col = ft_pixel(255,255,255,255);
			else
				col = ft_pixel(0,0,0,255);
			xyo.x = x * mapS;
			xyo.y = y * mapS;
			ft_draw_box(xyo, col, cub);
			// break ;
		}
	}
}

void	ft_draw_background(void *param)
{
	t_cub	*cub;
	int	x;
	int	y;

	x = -1;
	cub = (t_cub*)param;
	while (++x < (int) cub->img->width)
	{
		y = -1;
		while (++y < (int) cub->img->height)
			mlx_put_pixel(cub->img, x, y, ft_pixel(0,0,0,255));
	}
}

void	ft_draw_player(void *param)
{
	t_cub	*cub;
	int	x;
	int	y;

	x = -1;
	cub = (t_cub*)param;
	while (++x <= (int) cub->player->width)
	{
		y = -1;
		while (++y <= (int) cub->player->height)
			mlx_put_pixel(cub->img, x + cub->player->x_pos, y + cub->player->y_pos, cub->player->colour);
	}
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		cub->player->y_pos -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		cub->player->y_pos += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player->x_pos -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player->x_pos += 5;
}

int ft_init_player(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->x_pos = 50;
	cub->player->y_pos = 50;
	cub->player->width = 8;
	cub->player->height = 8;
	cub->player->colour = ft_pixel(255, 0, 0, 255);
	return (0);
}

int	ft_init_cub(t_cub *cub)
{
	if (ft_init_player(cub))
		return (1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!(cub->img))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_cub	cub;

	(void)argc;
	(void)argv;
	if (ft_init_cub(&cub))
		return (1);
	mlx_loop_hook(cub.mlx, ft_draw_background, &cub);
	mlx_loop_hook(cub.mlx, ft_draw_walls, &cub);
	mlx_loop_hook(cub.mlx, ft_draw_player, &cub);
	mlx_loop_hook(cub.mlx, ft_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}
