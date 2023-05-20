/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:37:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/21 01:12:14 by bmacmaho         ###   ########.fr       */
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

# define PI 3.1415926

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_vect
{
	float	delta_x;
	float	delta_y;
	int		angle;
}				t_vect;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_rays
{
	int 	ray;
	int		ray_angle;
	int		h_dist;
	int		v_dist;
	int		dist;
	int		colour;
	t_point	ray_end;
}				t_rays;

typedef struct s_player
{
	t_point	pos;
	t_vect	dir;
}				t_player;

typedef struct s_cub {
	t_player			*player;
	mlx_t				*mlx;
	mlx_image_t			*img;
	t_rays				*rays;
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
void	ft_2d_grid(void *v_cub);
void	ft_draw_player(void *v_cub);

//raycasting
void	ft_raycast(void *v_cub);
int		ft_is_wall(t_cub *cub);
int		ft_dist_to_next_v_gridline(t_cub *cub);
int		ft_dist_to_next_h_gridline(t_cub *cub);

//utils
float	ft_deg_to_rad(int degrees);
int		ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_safe_draw(mlx_image_t *img, int x, int y, int colour);
int		ft_fix_angle(int deg);

//errors & exit
int		ft_clean_exit(int stat, t_cub *cub);

#endif