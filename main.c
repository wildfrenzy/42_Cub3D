/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:50:27 by nmaliare          #+#    #+#             */
/*   Updated: 2023/05/14 15:28:43 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	map[] = {
// 	1,1,1,1,1,1,1,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,0,0,0,0,0,1,
// 	1,0,1,0,0,0,0,1,
// 	1,0,1,0,0,0,0,1,
// 	1,1,1,1,1,1,1,1,
// };
// int	mapX;
// int mapY;
// int mapS;

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// void	ft_draw_line(t_pixel a, t_pixel b, t_cub *cub)
// {
// 	float	delta_x;
// 	float	delta_y;
// 	int		colour = a.colour;
// 	delta_x = b.x - a.x;
// 	delta_y = b.y - a.y;
// 	while((int) (a.x - b.x) || (int) (a.y - b.y))
// 	{
// 		mlx_put_pixel(cub->img, a.x, a.y, a.colour);
// 		a.x += delta_x;
// 		a.y += delta_y;
// 		if (a.x > cub->img->width || a.y > cub->img->height ||\
// 			a.x < 0 || a.y < 0)
// 			break ;
// 	}
// }
// void	ft_draw_box(t_pixel xyo, int32_t colour, t_cub *cub)
// {
// 	t_pixel corners[4];
// 	int i;
// 	corners[0].x = xyo.x;
// 	corners[0].y = xyo.y;
// 	corners[1].x = xyo.x;
// 	corners[1].y = xyo.y + mapS;
// 	corners[2].x = xyo.x + mapS;
// 	corners[2].y = xyo.y + mapS;
// 	corners[3].x = xyo.x + mapS;
// 	corners[3].y = xyo.y;
// 	i = -1;
// 	while(++i < 4)
// 		corners[i].colour = colour;
// 	ft_draw_line(corners[0], corners[1], cub);
// 	ft_draw_line(corners[0], corners[2], cub);
// 	ft_draw_line(corners[1], corners[3], cub);
// 	ft_draw_line(corners[2], corners[3], cub);
// }
// void	ft_draw_map(void *param)
// {
// 	t_cub *cub;
// 	t_pixel xyo;
// 	cub = param;
// 	for (int y= 0; y <mapY; y++)
// 	{
// 		for (int x = 0; x< mapX; x++)
// 		{
// 			xyo.x = x*mapS;
// 			xyo.y = y*mapS;
// 			ft_draw_box(xyo, ft_pixel(255,255,255,255), cub);
// 		}
// 	}
// }

void	ft_draw_background(void *param)
{
	t_cub	*cub;
	int	x;
	int	y;

	x = -1;
	cub = (t_cub*)param;
	while (++x < (int) cub->background_img->width)
	{
		y = -1;
		while (++y < (int) cub->background_img->height)
			mlx_put_pixel(cub->background_img, x, y, ft_pixel(255,255,255,255));
	}
}
void	ft_draw_player(void *param)
{
	t_cub	*cub;
	int	x;
	int	y;

	x = -1;
	cub = (t_cub*)param;
	while (++x < (int) cub->player->width)
	{
		y = -1;
		while (++y < (int) cub->player->height)
			mlx_put_pixel(cub->player->img, x, y, cub->player->colour);
	}
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		cub->player->img->instances[0].y -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		cub->player->img->instances[0].y += 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player->img->instances[0].x -= 5;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player->img->instances[0].x += 5;
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
	cub->background_img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!(cub->background_img))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->background_img, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cub->player->img = mlx_new_image(cub->mlx, cub->player->width, cub->player->height);
	if (!(cub->player->img))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->player->img, cub->player->x_pos, cub->player->y_pos) == -1)
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
	ft_draw_background(&cub);
	// ft_draw_player(&cub);
	// mlx_loop_hook(cub.mlx, ft_draw_map, &cub);
	mlx_loop_hook(cub.mlx, ft_draw_player, &cub);
	mlx_loop_hook(cub.mlx, ft_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}
