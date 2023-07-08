/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:57 by barramacmah       #+#    #+#             */
/*   Updated: 2023/07/08 15:23:21 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initmap(t_colour *floor, t_colour *ceiling, t_cub *cub)
{
	floor->r = 0;
	floor->g = 0;
	floor->b = 0;
	floor->a = 0;
	ceiling->r = 0;
	ceiling->g = 0;
	ceiling->b = 0;
	ceiling->a = 0;
	cub->map.floor = *floor;
	cub->map.ceiling = *ceiling;
	cub->map.map = NULL;
	cub->map.no = NULL;
	cub->map.so = NULL;
	cub->map.we = NULL;
	cub->map.ea = NULL;
	cub->map.map_x = 0;
	cub->map.map_y = 0;
	cub->map.mapsize = 0;
	cub->map.all_info = 0;
	cub->map.pos.y = 0;
	cub->map.pos.x = 0;
	cub->map.pos.dir = 127;
}

int	ft_map(t_cub *cub, char *file, int *how_long_till_map)
{
	t_colour	floor;
	t_colour	ceiling;

	ft_initmap(&floor, &ceiling, cub);
	if (!gather_data(&(cub->map), file, how_long_till_map) \
		|| !create_int_map(&(cub->map)) || !fill_that_map(cub, file, \
		*how_long_till_map) || !validate_walls(&(cub->map)))
		return (1);
	return (0);
}

void	ft_init_player(t_cub *cub)
{
	cub->player.pos.x = cub->map.pos.x + 0.5;
	cub->player.pos.y = cub->map.pos.y + 0.5;
	cub->player.plane.x = 0.0;
	cub->player.plane.y = 0.66;
	cub->player.dir.x = 1;
	cub->player.dir.y = 0;
	if (cub->map.pos.dir == 'N')
		rotate(cub, M_PI * 1.5);
	else if (cub->map.pos.dir == 'W')
		rotate(cub, M_PI);
	else if (cub->map.pos.dir == 'S')
		rotate(cub, M_PI / 2);
}

int	ft_init_cub(t_cub *cub, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
		return (1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (2);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (3);
	return (0);
}
