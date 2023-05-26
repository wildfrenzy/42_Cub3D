/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:37:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/26 01:10:41 by bmacmaho         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vect
{
	float	angle;
	float	delta_x;
	float	delta_y;
}				t_vect;

typedef struct s_delta
{
	float	x;
	float	y;
}				t_delta;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_hv
{
	float	dist;
	int		colour;
	t_point	end;
	t_delta	delta;
}				t_hv;

typedef struct s_rays
{
	int		ray;
	float	ray_angle;
	int		left;
	int		up;
	t_hv	horizontal;
	t_hv	vertical;
	t_hv	*shortest;
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
int		ft_init_map(t_cub *cub, int argc, char **argv);
int		ft_init_rays(t_cub *cub);
int		ft_init_cub(t_cub *cub, int argc, char **argv);
int		ft_init_player(t_cub *cub);

//draw
void	ft_line(mlx_image_t *img, t_point p1, t_point p2, int colour);
void	ft_empty_square(mlx_image_t *img, t_point nw, t_point se, int colour);
void	ft_filled_square(mlx_image_t *img, t_point nw, t_point se, int colour);
void	ft_2d_grid(void *v_cub);
void	ft_draw_player(void *v_cub);
void	ft_background(void *v_cub);

//raycasting
void	ft_raycast(void *v_cub);
void	ft_ray_quadrant(t_cub *cub);
float	ft_check_vertical(t_cub *cub);
float	ft_check_horizontal(t_cub *cub);
int		ft_is_wall(t_cub *cub, t_point *ray_end);
float	ft_hv_angle(float angle);
int		ft_v_delta_x(t_cub *cub, int x);
int		ft_h_delta_y(t_cub *cub, int y);

//screen
void	ft_draw_ray(t_cub *cub);

//utils
float	ft_deg_to_rad(float degrees);
int		ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	ft_safe_draw(mlx_image_t *img, int x, int y, int colour);
float	ft_fix_angle(float deg);
int		ft_onscreen(t_point	*pixel);

//errors & exit
int		ft_clean_exit(int stat, t_cub *cub);
int		ft_print_error(int stat);

#endif