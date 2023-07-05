/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 23:48:41 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/05 14:56:15 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	check_wall(int x, int y, t_cub *cub, int *wall_x, int *wall_y)
{
	int m_index;

	// checking 1 previous pixel was ceiling or not;
	if (y > 0)
	{
		m_index = ((y - 1) * cub->img->width + x) * 4;
		if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 184 && cub->img->pixels[m_index + 2] == 65))
			*wall_y = y;
		else if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 158 && cub->img->pixels[m_index + 2] == 54))
			*wall_y = y;
	}
	if (x > 0)
	{
		m_index = (y * cub->img->width + x - 1) * 4;
		if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 184 && cub->img->pixels[m_index + 2] == 65))
			*wall_x = x;
		else if (!(cub->img->pixels[m_index] == 222 && cub->img->pixels[m_index + 1] == 158 && cub->img->pixels[m_index + 2] == 54))
			*wall_x = x;
	}
}*/

#define MAX_DIST  float(16.) / sin(PI * 45.0)/180.) //16 - mapX

const float HEIGHT_FAR  = 1.0f / 8.0f;
const float HEIGHT_NEAR = 2.0f / 3.0f;

float get_wall_height(float dist)
{
	//MAX_DIST * HEIGHT_FAR / dist;
	return 16.0f/sin(3.1415926 * 45.0) / 180. * 0.125 / dist;
}

typedef struct vec{
	float r;
	float g;
	float b;
	float a;
}			t_vec;

float fract(float x)
{
	return x - floor(x);
}

/*
int shader_toy2(t_cub *cub, int x, int y)
{
	float height = get_wall_height(cub->rays->shortest->dist);
	float lower_bound = (1.0 - height) / 2.0;
	float upper_bound = 1.0 - (1.0 - height) / 2.0;

	t_dpoint uv;
	mlx_image_t *texture1 = cub->map.north;
	mlx_image_t *texture2 = cub->map.south;

	uv.x = x/cub->mlx->width;
	uv.y = y/cub->mlx->height;

	if (uv.y > lower_bound && uv.y < upper_bound){
		double t_x =  cub->rays->is_vertical ? fract(uv.x) : fract(uv.y);
		double t_y =  ((uv.y - lower_bound) / height) ;
		//printf("height [%f]\n", height);

		int tx;
		int ty;
		uint32_t t_index;

		if (cub->rays->shortest->colour == cub->rays->horizontal.colour) //orange
		{
			double pos_x = t_x * (texture1->width - 1);
			double pos_y = t_y * (texture1->width - 1);

			//int i_x = (int) (pos_x + 0.5);
			//int i_y = (int) (pos_y + 0.5);

			tx = (int)pos_x; //% texture1->width;
			ty = (int)pos_y;// % texture1->height;
			t_index = (ty * texture1->width + tx) * 4;
			return ft_rgba_to_int(texture1->pixels[t_index], texture1->pixels[t_index + 1], texture1->pixels[t_index + 2], 255);
		}
		else if (cub->rays->shortest->colour == cub->rays->vertical.colour) //yellow
		{
			double pos_x = t_x * (texture2->width - 1);
			double pos_y = t_y * (texture2->width - 1);

			int i_x = (int) (pos_x + 0.5);
			int i_y = (int) (pos_y + 0.5);

			tx = i_x % texture2->width;
			ty = i_y % texture2->height;
			t_index = (ty * texture2->width + tx) * 4;
			return ft_rgba_to_int(texture2->pixels[t_index], texture2->pixels[t_index + 1], texture2->pixels[t_index + 2], 255);
		}


	}
	return 0;
}

int shader_toy(t_cub *cub, t_point	top)
{
	float height = get_wall_height(cub->rays->shortest->dist);
	float lower_bound =       (1.0 - height) / 2.0;
	float upper_bound = 1.0 - (1.0 - height) / 2.0;

	t_dpoint uv;
	t_colour color;


	mlx_image_t *main = cub->img;
	mlx_image_t *texture1 = cub->map.north;
	mlx_image_t *texture2 = cub->map.south;


	//t_vec vec4 = {0.2, 0.2, 0.2, 0.1};

	// Normalized pixel coordinates (from 0 to 1)
	uv.x = top.x/cub->mlx->width;
	uv.y = top.y/cub->mlx->height;

//	uv.x = fract(uv.x * 4.);
//	uv.y = fract(uv.y * 4.);


	if (uv.y > lower_bound && uv.y < upper_bound) { // draw wall column

								// texture, coords on texture


		double t_x =  cub->rays->is_vertical ? (top.x) : (top.y);
		double t_y =  ((uv.y - lower_bound) / height) ;

		printf(">>> tx[%f], ty[%f] height [%f]\n", t_x, t_y, height);

		int tx;
		int ty;
		uint32_t t_index;

		if (cub->rays->shortest->colour == cub->rays->horizontal.colour) //orange
		{
			//double pos_x = t_x * (texture1->width - 1);
			double pos_y = t_y * (texture1->height - 1);

			//int i_x = (int) (pos_x + 0.5);
			int i_y = (int) (pos_y + 0.5);
//			if (i_y < 0)
//				i_y = 0;
//			else if (i_y >= texture1->height)
//				i_y = texture1->height - 1;
//
			if(t_x >= texture1->width)
				t_x = texture1->width - 1;

			printf(">>> iy[%d]\n", i_y);
			tx = (int)t_x % texture1->width;
			ty = i_y % texture1->height;
			t_index = (ty * texture1->width + tx) * 4;
			return ft_rgba_to_int(texture1->pixels[t_index], texture1->pixels[t_index + 1], texture1->pixels[t_index + 2], 255);
		}
		else if (cub->rays->shortest->colour == cub->rays->vertical.colour) //yellow
		{
		//	double pos_x = t_x * (texture2->width * texture2->height - 1);
			double pos_y = t_y * (texture2->height - 1);

		//	int i_x = (int) (pos_x + 0.5);
			int i_y = (int) (pos_y + 0.5);

//			if (i_y < 0)
//				i_y = 0;
//			else if (i_y >= texture2->height)
//				i_y = texture2->height - 1;

			tx = (int)t_x % texture2->width;
			ty = i_y % texture2->height;
			printf(">>> iy[%d]\n", i_y);
			t_index = (ty * texture2->width + tx) * 4;
			return ft_rgba_to_int(texture2->pixels[t_index], texture2->pixels[t_index + 1], texture2->pixels[t_index + 2], 255);
		}

		// texture x : cub->rays->is_vertical ? fract(cub->rays->shortest->end.x) : fract(cub->rays->shortest->end.y)
		// texture y: (uv.y - lower_bound) / height)

		//t_vec tex_color = texture(iChannel0, vec2(, );

		// for mixing alpha channel; in shadertoy its for shadow on wall. we dont need it
		//color = mix(tex_color, vec4, 0.0f); //rgb[a] : res.is_vertical ? 0.0 : 0.3 defines 1 wall or another, yellow or orange in our case
	}
	return (0);
}
*/

int *get_textel(t_cub *cub, int wall_height)
{
	uint32_t x;
	uint32_t y;

	uint32_t tx;
	uint32_t ty;

	uint32_t t_index;

	int color = 0;

	//printf("wall h: %d", wall_height);
	int *arr = calloc(wall_height, 4);

	if (cub->rays->shortest->colour == ft_rgba_to_int(222, 184, 65, 255))
	{
		x = (int)floor(cub->rayend_h->relative_x * cub->map.north->width);
		y = (int)floor(cub->rayend_h->relative_y * cub->map.north->height);

		//tx = x % cub->map.north->width;
		//ty = y % cub->map.north->height;

		//t_index = (ty * cub->map.north->width + tx) * 4;
		//color = ft_rgba_to_int(cub->map.north->pixels[t_index],cub->map.north->pixels[t_index + 1], cub->map.north->pixels[t_index + 2], 255);

		int i = -1;
		long long too_long = cub->map.north->width * cub->map.north->height * 4;
		while (++i < wall_height)
		{
			//y += i;

			//tx = x % cub->map.north->width;
			//ty = y % cub->map.north->height;
			t_index = ((y + i) * cub->map.north->width + x) * 4;
			if (t_index >= too_long)
				break;
			color = ft_rgba_to_int(cub->map.north->pixels[t_index],cub->map.north->pixels[t_index + 1], cub->map.north->pixels[t_index + 2], 255);
			arr[i] = color;
		}

	}
	else if (cub->rays->shortest->colour == ft_rgba_to_int(222, 158, 54, 255))
	{
		x = (int)floor(cub->rayend_h->relative_x * cub->map.south->width);
		y = (int)floor(cub->rayend_v->relative_y * cub->map.south->height);

		//t_index = (y * cub->map.south->width + x) * 4;
		//color = ft_rgba_to_int(cub->map.south->pixels[t_index],cub->map.south->pixels[t_index + 1], cub->map.south->pixels[t_index + 2], 255);

		int i = -1;
		long long too_long = cub->map.south->width * cub->map.south->height * 4;

		while (++i < wall_height)
		{
			//y += i;

			//tx = x % cub->map.south->width;
			//ty = y % cub->map.south->height;

			t_index = ((y + i)* cub->map.south->width + x) * 4;
			//printf("t index[%d]\n", t_index);
			if (t_index >= too_long)
			{

				break;
			}
			color = ft_rgba_to_int(cub->map.south->pixels[t_index],cub->map.south->pixels[t_index + 1], cub->map.south->pixels[t_index + 2], 255);
			arr[i] = color;
		}

	}
	return arr;
}

void ft_trytexture(void *param)
{
	t_cub *cub;

	cub = param;

	mlx_image_t *main = cub->img;
	mlx_image_t *texture1 = cub->map.north;
	mlx_image_t *texture2 = cub->map.south;

//	mlx_resize_image(texture1, 200, 200);
//	mlx_resize_image(texture2, 200, 200);

	int tx;
	int ty;
	uint32_t t_index;
	uint32_t m_index;

	int wall_y = 0;
	int wall_x = 0;

	int stop = 3;

	//printf("mlx_wh[%d][%d] main_wh[%d][%d]\n", cub->mlx->width,cub->mlx->height, main->width, main->height);
	for (int y = 0; y < cub->mlx->height; y++) {
		for (int x = 0; x < cub->mlx->width; x++) {
			if (x > main->width || y > main->height)
			{
				printf("You've gone too far [impossible. almost]\n");
				return ;
			}
			m_index = (y * main->width + x) * 4;

			// orange wall - one texture
			if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 184 && main->pixels[m_index + 2] == 65) {

			//	check_wall(x, y, cub, &wall_x, &wall_y);

				//printf("w_x[%d] w_y [%d]\n", wall_x, wall_y);

				tx = x % texture1->width;
				ty = y % texture1->height; // y - y_coord where wall starts
				t_index = (ty * texture1->width + tx) * 4;

				main->pixels[m_index] = texture1->pixels[t_index];
				main->pixels[m_index + 1] = texture1->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture1->pixels[t_index + 2];
			}
			// yellow wall - another texture
			else if (main->pixels[m_index] == 222 && main->pixels[m_index + 1] == 158 && main->pixels[m_index + 2] == 54) {

			//	check_wall(x, y, cub, &wall_x, &wall_y);

				tx = x % texture2->width;
				ty = y  % texture2->height;
				t_index = (ty * texture2->width + tx) * 4;

				main->pixels[m_index] = texture2->pixels[t_index];
				main->pixels[m_index + 1] = texture2->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture2->pixels[t_index + 2];
			}
		}
		/*printf("y [%d]\n", y);
		stop--;
		if (stop == 0)
			return;*/

	}
}

int	load_texture(mlx_t	*mlx, mlx_image_t **img, char *file)
{
	xpm_t	*texture;

	texture = mlx_load_xpm42(file);
	if (!texture)
	{
		perror("Error\n");
		return (0);
	}
	*img = mlx_texture_to_image(mlx, &(texture->texture));
	printf("img: %dpx %dpx\n", (*img)->width, (*img)->height);
	mlx_delete_xpm42(texture);
	return 1;
}

int	prepare_textures(t_cub *cub)
{
	if (!load_texture(cub->mlx, &(cub->map.north), cub->map.no))
		return 0;
	if (!load_texture(cub->mlx, &(cub->map.south), cub->map.so))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		return 0;
	}
	if (!load_texture(cub->mlx, &(cub->map.east), cub->map.ea))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		return 0;
	}
	if (!load_texture(cub->mlx, &(cub->map.west), cub->map.we))
	{
		mlx_delete_image(cub->mlx, cub->map.north);
		mlx_delete_image(cub->mlx, cub->map.south);
		mlx_delete_image(cub->mlx, cub->map.east);
		return 0;
	}
	return 1;
}