/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:37:23 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/18 23:39:00 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 320
# define HEIGHT 200

typedef struct s_player
{
	float   x_pos;
	float   y_pos;
	float   direction;
}				t_player;

typedef struct s_cub {
	t_player			*player;
	mlx_t				*mlx;
	struct mlx_image	*img;
	// t_rays				*rays;
	// t_map				*map;
}				t_cub;

//controls
void	ft_hook(void *param);

// inits
int ft_init_cub(t_cub *cub, int argc, char **argv);
int ft_init_player(t_cub *cub);

//errors & exit
int ft_clean_exit(int stat, t_cub *cub);

#endif