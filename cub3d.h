/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:50:15 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/12 19:20:56 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "MLX42/include/MLX42/MLX42.h"

# define WIDTH 512
# define HEIGHT 512 

typedef struct	s_player {
	int32_t	x_pos;
	int32_t	y_pos;
	int32_t	colour;
}				t_player;

typedef struct	s_cub {
	t_player			*player;
	struct mlx_image	*img;
	mlx_t				*mlx;
}				t_cub;

#endif