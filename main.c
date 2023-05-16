/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:50:27 by nmaliare          #+#    #+#             */
/*   Updated: 2023/05/16 22:09:22 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map[] = {
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};
int	mapX = 8;
int mapY = 8;
int mapS = 64;

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_draw_box(t_pixel xyo, int32_t colour, t_cub *cub, int32_t height, int32_t width)
{
	t_pixel corners[4];
	int i;

	corners[0].x = xyo.x + 1;
	corners[0].y = xyo.y + 1;
	corners[1].x = xyo.x + 1;
	corners[1].y = xyo.y + height - 1;
	corners[2].x = xyo.x + width - 1;
	corners[2].y = xyo.y + height - 1;
	corners[3].x = xyo.x + width - 1;
	corners[3].y = xyo.y + 1;
	i = -1;
	while(corners[0].y <= corners[1].y)
	{
		ft_line(cub->img, &corners[0], &corners[3], colour);
		corners[0].y++;
		corners[3].y++;
	}
}

void	ft_draw_walls(void *param)
{
	t_cub *cub;
	t_pixel xyo;
	cub = param;
	int32_t col;
	
	for (int y= 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			if(map[y * mapX + x] == 1)
				col = ft_pixel(255,255,255,255);
			else
				col = ft_pixel(0,0,0,255);
			xyo.x = x * mapS;
			xyo.y = y * mapS;
			ft_draw_box(xyo, col, cub, mapS, mapS);
		}
	}
}

void	ft_draw_background(void *param)
{
	t_cub	*cub;
	int	x;
	int	y;
	int colour;

	x = -1;
	cub = (t_cub*)param;
	while (++x < (int) cub->img->width)
	{
		y = -1;
		while (++y < (int) cub->img->height)
		{
			if (y > 160)
				colour = ft_pixel(255,255,255,255);
			else	
				colour = ft_pixel(100,100,100,255);
			mlx_put_pixel(cub->img, x, y, colour);
		}
	}
}

int	ft_onscreen(int x, int y)
{
	if(x < 0)
		return (0);
	if (x >= WIDTH)
		return (0);
	if (y < 0)
		return (0);
	if (y >= HEIGHT)
		return (0);
	return (1);
}

void	ft_draw_player(void *param)
{
	t_cub	*cub;
	t_pixel	p_loc;
	t_pixel line_end;
	int	x;
	int	y;

	x = -1;
	cub = (t_cub*)param;
	while (++x <= (int) cub->player->width)
	{
		y = -1;
		while (++y <= (int) cub->player->height)
		if (ft_onscreen(x + cub->player->x_pos - cub->player->width/2, y + cub->player->y_pos - cub->player->height/2))
			mlx_put_pixel(cub->img, x + cub->player->x_pos, y + cub->player->y_pos, cub->player->colour);
	}
	p_loc.x = cub->player->x_pos + (cub->player->width / 2);
	p_loc.y = cub->player->y_pos + (cub->player->height / 2);
	p_loc.colour = cub->player->colour;
	line_end.x = p_loc.x + cub->player->delta_x * 5;
	line_end.y = p_loc.y + cub->player->delta_y * 5;
	line_end.colour = cub->player->colour;
	ft_line(cub->img, &p_loc, &line_end, cub->player->colour);
}

void ft_preline(t_cub *cub, t_rays *ray)
{
	t_pixel	one;
	t_pixel two;

	one.x = cub->player->x_pos + cub->player->width/ 2;
	one.y = cub->player->y_pos + cub->player->height / 2;
	two.x = ray->rx;
	two.y = ray->ry;
	ft_line(cub->img, &one, &two, cub->player->colour);
}

void	ft_draw_3d(void *param)
{
	t_cub *cub;
	float lineH;
	float lineO;
	t_pixel line_r_corner;
	
	cub = param;
	lineH = (mapS * 320) / cub->rays->disT;
	if (lineH > 320)
		lineH = 320;
	lineO = 160 - lineH / 2;
	line_r_corner.x = cub->rays->r*8 + 530;
	line_r_corner.y = 160 - lineH / 2; 
	ft_draw_box(line_r_corner, cub->rays->colour, cub, (int) lineH, 12);
}

int fix_angle(int a)
{
	if (a > 359)
		a -= 360;
	else if (a < 0)
		a += 360;
	return (a);
}

float	degrees_to_radians(int a)
{
	return (a * M_PI/180.0);
}

void ft_draw_rays(void *param)
{
	t_cub	*cub;
	cub = (t_cub*) param;
	t_rays	*rays;

	rays = cub->rays;
	rays->disH = 1000000;
	rays->disV = 1000000;
	rays->hx = cub->player->x_pos;
	rays->hy = cub->player->y_pos;
	rays->vx = cub->player->x_pos;
	rays->vy = cub->player->y_pos;
	rays->ra = fix_angle(cub->player->angle + 30);
	rays->r = -1;
	while (++rays->r < 60)
	{
		rays->dof = 0;
		rays->Tan = tan(degrees_to_radians(rays->ra));
		if(cos(degrees_to_radians(rays->ra)) > 0.001)
		{
			rays->rx = (((int)cub->player->x_pos>>6)<<6) + mapS;
			rays->ry = (cub->player->x_pos - rays->rx) * rays->Tan + cub->player->y_pos;
			rays->xo = mapS;
			rays->yo = -rays->xo * rays->Tan;
		}	
		else if(cos(degrees_to_radians(rays->ra)) < -0.001)
		{
			rays->rx = (((int)cub->player->x_pos>>6)<<6) - 0.001;
			rays->ry = (cub->player->x_pos - rays->rx) * rays->Tan + cub->player->y_pos;
			rays->xo = -mapS;
			rays->yo = -rays->xo *rays-> Tan;
		}
		else
		{
			rays->rx = cub->player->x_pos;
			rays->ry = cub->player->y_pos;
			rays->dof = 8;
		}
		while (rays->dof < 8)
		{
			rays->mx = (int) (rays->rx) >> 6; 
			rays->my = (int) (rays->ry) >> 6;
			rays->mp = rays->my *mapX + rays->mx;
			if (rays->mp > 0 && rays->mp < mapX * mapY && map[rays->mp] == 1)
			{
				rays->vx = rays->rx;
				rays->vy = rays->ry;
				rays->disV = cos(degrees_to_radians(rays->ra)) * (rays->rx-cub->player->x_pos)- sin(degrees_to_radians(rays->ra)) * (rays->ry - cub->player->y_pos);
				rays->dof = 8;
			}
			else
			{
				rays->rx += rays->xo;
				rays->ry += rays->yo;
				rays->dof += 1;
			}
		}
		rays->dof = 0;
		rays->Tan = 1.0/rays->Tan;
		if(sin(degrees_to_radians(rays->ra)) > 0.001)
		{
			rays->ry = (((int)cub->player->y_pos>>6)<<6)-0.0001;
			rays->rx = (cub->player->y_pos - rays->ry) * rays->Tan + cub->player->x_pos;
			rays->yo = -mapS;
			rays->xo = -rays->yo * rays->Tan;
		}	
		else if(sin(degrees_to_radians(rays->ra)) <- 0.001)
		{
			rays->ry = (((int)cub->player->y_pos>>6)<<6) + mapS;
			rays->rx = (cub->player->y_pos - rays->ry) * rays->Tan + cub->player->x_pos;
			rays->yo = mapS;
			rays->xo = -rays->yo * rays->Tan;
		}
		else
		{
			rays->rx = cub->player->x_pos;
			rays->ry = cub->player->y_pos;
			rays->dof = 8;
		}
		while (rays->dof < 8)
		{
			rays->mx = (int) (rays->rx) >> 6; 
			rays->my = (int) (rays->ry) >> 6;
			rays->mp = rays->my * mapX + rays->mx;
			if (rays->mp > 0 && rays->mp < mapX * mapY && map[rays->mp] == 1)
			{
				rays->hx = rays->rx;
				rays->hy = rays->ry;
				rays->disH = cos(degrees_to_radians(rays->ra))*(rays->rx-cub->player->x_pos)-sin(degrees_to_radians(rays->ra))*(rays->ry-cub->player->y_pos);
				rays->dof = 8;
			}
			else
			{
				rays->rx += rays->xo;
				rays->ry += rays->yo;
				rays->dof += 1;
			}
		}
		
		if(rays->disV <= rays->disH)
		{
			rays->rx = rays->vx;
			rays->ry = rays->vy;
			rays->disT = rays->disV;
			rays->colour = ft_pixel(200, 0, 0, 255);
		}
		else
		{
			rays->rx = rays->hx;
			rays->ry = rays->hy;
			rays->disT = rays->disH;
			rays->colour = ft_pixel(255,0,0,255);
		}
		ft_preline(cub, rays);
		ft_draw_3d(cub);
		rays->ra = fix_angle(rays->ra - 1);
		printf("ID: %d dt: %3.3f dv: %3.3f dh: %3.3f, \n", rays->r, rays->disT, rays->disV, rays->disH);
	}
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP))
	{
		cub->player->y_pos += cub->player->delta_y * 5;
		cub->player->x_pos += cub->player->delta_x * 5;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
	{
		cub->player->y_pos -= cub->player->delta_y * 5;
		cub->player->x_pos -= cub->player->delta_x * 5;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player->angle += 5;
		cub->player->angle = fix_angle(cub->player->angle);
		cub->player->delta_x = cos(degrees_to_radians(cub->player->angle));
		cub->player->delta_y = -sin(degrees_to_radians(cub->player->angle));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player->angle -= 5;
		cub->player->angle = fix_angle(cub->player->angle);
		cub->player->delta_x = cos(degrees_to_radians(cub->player->angle));
		cub->player->delta_y = -sin(degrees_to_radians(cub->player->angle));
	}
}

int ft_init_player(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (1);
	cub->player->x_pos = 100;
	cub->player->y_pos = 100;
	cub->player->angle = 90;
	cub->player->delta_x = cos(degrees_to_radians(cub->player->angle));
	cub->player->delta_y = -sin(degrees_to_radians(cub->player->angle));
	cub->player->width = 8;
	cub->player->height = 8;
	cub->player->colour = ft_pixel(255, 0, 0, 255);
	return (0);
}

int	ft_init_cub(t_cub *cub)
{
	if (ft_init_player(cub))
		return (1);
	cub->rays = malloc(sizeof(t_rays));
	if (!cub->rays)
	{
		free(cub->player);
		return (1);
	}
	cub->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!(cub->img))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_cub	cub;

	(void)argc;
	(void)argv;
	if (ft_init_cub(&cub))
		return (1);
	ft_start(&cub);
	return (EXIT_SUCCESS);
}
