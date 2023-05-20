/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:37:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/20 16:52:08 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 640
# define HEIGHT 480

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_player
{
	t_point	position;
	float	direction;
}				t_player;

typedef struct s_cub {
	t_player			*player;
	mlx_t				*mlx;
	mlx_image_t			*img;
	// t_rays				*rays;
	// t_map				*map;
}				t_cub;

//controls
void	ft_hook(void *param);

// inits
int		ft_init_cub(t_cub *cub, int argc, char **argv);
int		ft_init_player(t_cub *cub);

//draw
void	ft_line(mlx_image_t *img, t_point p1, t_point p2, int colour);
void	ft_empty_square(mlx_image_t *img, t_point nw, t_point se, int colour);
void	ft_filled_square(mlx_image_t *img, t_point nw, t_point se, int colour);

//utils
float	ft_deg_to_rad(float degrees);
int		ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_safe_draw(mlx_image_t *img, int x, int y, int colour);

//errors & exit
int		ft_clean_exit(int stat, t_cub *cub);

#endif