/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:02:45 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/09 14:29:28 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/parsing.h"
# include "Libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.1415926

# define WIDTH 1200
# define HEIGHT 1000

typedef struct s_vect {
	double	angle;
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
}			t_vect;

typedef struct s_delta {
	double	x;
	double	y;
}				t_delta;

typedef struct s_dpoint {
	double	x;
	double	y;
}				t_dpoint;

typedef struct s_point {
	int	x;
	int	y;
}				t_point;

typedef struct s_hv {
	double		dist;
	int			colour;
	t_dpoint	end;
	t_delta		delta;
}				t_hv;

typedef struct s_player {
	t_dpoint	pos;
	t_vect		dir;
	t_dpoint	plane;
}				t_player;

typedef struct s_cub {
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_dpoint	ray;
	t_dpoint	side_dist;
	t_dpoint	delta_dist;
	double		perp_wall_dist;
	t_point		step;
	int			hit;
	int			side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	mlx_image_t	*chosen_texture;
	t_point		tex;
}				t_cub;

// controls
void			ft_hook(void *param);

// inits
int				ft_map(t_cub *cub, char *file, int *hltm);
int				ft_init_rays(t_cub *cub);
int				ft_init_cub(t_cub *cub, int argc, char **argv);
void			ft_init_player(t_cub *cub);

// draw
void			ft_line(mlx_image_t *img, t_point p1, t_point p2, int colour);
void			ft_empty_square(mlx_image_t *img, t_point nw, \
					t_point se, int colour);
void			ft_filled_square(mlx_image_t *img, t_point nw, \
					t_point se, int colour);
void			ft_2d_grid(void *v_cub);
void			ft_draw_player(void *v_cub);
void			ft_background(void *v_cub);

// raycasting
void			choose_texture(t_cub *cub);
void			calc_step(t_cub *cub);
void			set_delta_dist(t_cub *cub);
void			put_textel(mlx_image_t *img, int x, int y, unsigned int colour);
unsigned int	get_color_textel(t_cub *cub, int x, int y);

// screen
void			ft_draw_ray(t_cub *cub);

// utils
double			ft_deg_to_rad(double degrees);
int				ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void			ft_safe_draw(mlx_image_t *img, int x, int y, int colour);
double			ft_fix_angle(double deg);
int				ft_onscreen(t_dpoint *pixel);

// errors & exit
int				ft_checkargs(int argc, char **argv);
int				ft_clean_exit(int stat, t_cub *cub);
int				ft_print_error(char *message);

// textures
int				prepare_textures(t_cub *cub);
int				load_texture(mlx_t *mlx, mlx_image_t **img, char *file);
void			ft_trytexture(void *param);
int				*get_textel(t_cub *cub, int wall_height);
void			new_ft_line(mlx_image_t *img, t_point p1, \
					t_point p2, int *colour);
float			get_wall_height(float dist);

//catjam
void			raycast_loop(void *param);
void			rotate(t_cub *cub, double rot_speed);

#endif
