/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:50:15 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/18 18:52:40 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"

# define PI 3.14159265359f
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533f

# define WIDTH 1280
# define HEIGHT 720

// typedef struct s_map
// {
// 	int	*map;
// 	int	mapX;
// 	int mapY;
// 	int mapS;
// }				t_map;

typedef struct s_pixel
{
	int32_t	x;
	int32_t	y;
	int32_t	colour;
}				t_pixel;

typedef struct s_rays
{
	int		colour;
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	Tan;
	float	disH;
	float	disV;
	float	disT;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
}				t_rays;

typedef struct s_player
{
	float				x_pos;
	float				y_pos;
	float				delta_x;
	float				delta_y;
	float				angle;
	int32_t				width;
	int32_t 			height;
	int32_t				colour;
}				t_player;

typedef struct s_cub {
	t_player			*player;
	mlx_t				*mlx;
	struct mlx_image	*img;
	t_rays				*rays;
	// t_map				*map;
}				t_cub;

//for drawing
void	ft_line(mlx_image_t *img, t_pixel *p1, t_pixel *p2, int colour);
void	ft_draw_rays(void *param);
void	ft_draw_3d(void *param);
void	ft_draw_player(void *param);
void	ft_draw_background(void *param);
void	ft_draw_walls(void *param);
void	ft_draw_box(t_pixel xyo, int32_t colour, t_cub *cub, int32_t height, int32_t width);

//engine
void	ft_start(t_cub *cub);
void	ft_hook(void *param);

#endif