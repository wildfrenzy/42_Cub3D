/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:31:50 by nmaliare          #+#    #+#             */
/*   Updated: 2023/06/18 23:12:21 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# include "get_next_line.h"

typedef struct s_cub t_cub;

//check if we need typedef for norm ?
enum position
{
	first, middle, last
};

/*typedef struct s_player
{
	int	x;
	int	y;
	char	dir; //N,S,E,W
}				t_player;*/

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
}				t_colour;

typedef struct s_map
{
	int *map;
	int mapX;
	int mapY;
	int all_info;
	char *no;
	char *so;
	char *we;
	char *ea;

	t_colour floor;
	t_colour ceiling;
	//t_player player;
}				t_map;

/*	parse	*/
int		fill_that_map(t_cub *cub, char *file, int how_long_till_map);
int		gather_data(t_map *map, char *av, int *lines);

/*	map parse	*/

int		validate_map_line(char *line);
int		check_top(t_map *map, int i, int position);
int		check_bot(t_map *map, int i, int position);
int		check_first_row(t_map *map);
int		check_last_row(t_map *map);
int		validate_walls(t_map *map);

/*	map creator	*/
int		init_map(t_map *map);
int		create_int_map(t_map *map);
int		get_width_height(int fd, t_map *map, char *buf);
int		add_in_map(char *buff, t_cub *cub, int *tmp);
void	add_player(char *buff, t_cub *cub, int *tmp, int i);

/*	colours	*/

int		check_rgb(char *rgb, int colour);
int		check_colours(t_map *map);
int		get_colour(t_map *map, char color, char *buf);
int		write_rgb(char *rgb, t_map *map, char where, int colour);

/*	textures	*/

int		get_texture(t_map *map, char texture, char *buf);
int		check_if_texture_exists(t_map *map, char texture);

/*	add utils	*/

int		check_file(char *file);
int		skip_spaces(char *buf, int i);
int		scroll_to_map(int fd, int how_long);
int		mapline(char *buf);

/*	freedom	*/

int		freebuf_closefd(char *buf, int fd);
int		free_map(t_map *map);
