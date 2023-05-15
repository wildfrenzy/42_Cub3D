/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:50:15 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/15 22:53:15 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_pixel
{
	int32_t	x;
	int32_t y;
	int32_t colour;
}				t_pixel;

// typedef struct s_map
// {
// 	int	*map;
// 	int	mapX;
// 	int mapY;
// 	int mapS;
// }				t_map;

typedef struct s_rays
{
	int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
	float	nTan;
	float	disH;
	float	disV;
	float	disT;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	int		colour;
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


void	ft_line(mlx_image_t *img, t_pixel *p1, t_pixel *p2, int colour);

#endif