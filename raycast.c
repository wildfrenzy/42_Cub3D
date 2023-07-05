/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:09:09 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/06/24 22:52:07 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

extern int blockS;

double ft_distance_between_2_points(t_point p1, t_dpoint *p2) {
  return (sqrt(pow(p2->x - p1.x, 2) + pow(p2->y - p1.y, 2)));
}

int ft_is_wall(t_cub *cub, t_dpoint *ray_end) {
  t_point cell;
  int index;

  cell.x = (int)(ray_end->x + (double)cub->rays->left) / blockS;
  cell.y = (int)(ray_end->y + (double)cub->rays->up) / blockS;
  index = cell.y * cub->map.mapX + cell.x;
  // printf("index[%d] of %d\n", index, cub->map.mapX * cub->map.mapY);

  if (index < cub->map.mapsize && cub->map.map[index] == 1)
    return (1);
  else
    return (0);
}

t_dpoint *ft_check_horizontal_total(t_cub *cub) {
  double o;
  double a;
  double angle;
  double xoff;
  double yoff;

  if (cub->rays->ray_angle == 0.0 || cub->rays->ray_angle == 360.0 ||
      cub->rays->ray_angle == 180.0)
    return (NULL);
  o = ft_blocksize_remainder(cub, cub->player.pos.y, 'h');
  angle = ft_corresponding_angle(cub->rays->ray_angle);
  cub->rayend_h = &cub->rays->horizontal.end;
  cub->rayend_h->y = (double)((cub->player.pos.y));
  cub->rayend_h->y += o * (double)cub->rays->up;
  cub->rayend_h->x = (double)cub->player.pos.x;
  a = o / tan(ft_deg_to_rad(angle));
  cub->rayend_h->x += a * cub->rays->left;
  if (cub->rays->left == -1 && a > cub->player.pos.x)
    return (NULL);
  if (cub->rays->left == 1 && a > (blockS * cub->map.mapX) - cub->player.pos.x)
    return (NULL);
  yoff = blockS * cub->rays->up;
  xoff = ((double)blockS) / tan(ft_deg_to_rad(angle)) * cub->rays->left;
  while (ft_onscreen(cub->rayend_h) && !ft_is_wall(cub, cub->rayend_h)) {
    cub->rayend_h->y += yoff;
    cub->rayend_h->x += xoff;
  }
  cub->rayend_h->relative_x =
      (cub->rayend_h->x - (floor(cub->rayend_h->x / blockS) * blockS)) / blockS;
  cub->rayend_h->relative_y =
      (cub->rayend_h->y - (floor(cub->rayend_h->y / blockS) * blockS)) / blockS;
  return (cub->rayend_h);
}

double ft_check_horizontal(t_cub *cub) {
  t_dpoint *rayend;

  rayend = ft_check_horizontal_total(cub);
  if (rayend == NULL)
    return (__FLT_MAX__);
  return (ft_distance_between_2_points(cub->player.pos, rayend));
}

t_dpoint *ft_check_vertical_total(t_cub *cub) {
  double a;
  double o;
  double angle;
  double xoff;
  double yoff;

  a = ft_blocksize_remainder(cub, cub->player.pos.x, 'v');
  angle = ft_corresponding_angle(cub->rays->ray_angle);
  cub->rayend_v = &cub->rays->vertical.end;
  cub->rayend_v->x = (double)cub->player.pos.x;
  cub->rayend_v->x += a * (double)cub->rays->left;
  cub->rayend_v->y = (double)((cub->player.pos.y));
  o = a * tan(ft_deg_to_rad(angle));
  cub->rayend_v->y += o * cub->rays->up;
  xoff = blockS * cub->rays->left;
  yoff = ((double)blockS) * tan(ft_deg_to_rad(angle)) * cub->rays->up;
  while (ft_onscreen(cub->rayend_v) && !ft_is_wall(cub, cub->rayend_v)) {
    cub->rayend_v->x += xoff;
    cub->rayend_v->y += yoff;
  }
  cub->rayend_v->relative_x =
      (cub->rayend_v->x - (floor(cub->rayend_v->x / blockS) * blockS)) / blockS;
  cub->rayend_v->relative_y =
      (cub->rayend_v->y - (floor(cub->rayend_v->y / blockS) * blockS)) / blockS;
  return (cub->rayend_v);
}

double ft_check_vertical(t_cub *cub) {
  t_dpoint *rayend;

  rayend = ft_check_vertical_total(cub);
  if (rayend == NULL)
    return (__FLT_MAX__);
  return (ft_distance_between_2_points(cub->player.pos, rayend));
}

void ft_ray_quadrant(t_cub *cub) {
  t_rays *ray;

  ray = cub->rays;
  if (ray->ray_angle > 0.0 && ray->ray_angle < 180.0)
    ray->up = -1;
  else
    ray->up = 1;
  if (ray->ray_angle > 90.0 && ray->ray_angle < 270.0)
    ray->left = -1;
  else
    ray->left = 1;
}

void ft_raycast(void *v_cub) {
  t_cub *cub;
  t_rays *rays;
//  t_dpoint *hit;

  cub = v_cub;
  rays = cub->rays;
  rays->ray = -1;
  rays->ray_angle = ft_fix_angle(cub->player.dir.angle + 30.0);
  while (++rays->ray < cub->mlx->width) {
    ft_ray_quadrant(cub);
    ft_check_vertical_total(cub); // huge optimisation possible
    ft_check_horizontal_total(cub);
    if (cub->rayend_v == NULL)
      rays->vertical.dist = __FLT_MAX__;
    else
      rays->vertical.dist =
          ft_distance_between_2_points(cub->player.pos, cub->rayend_v);
    if (cub->rayend_h == NULL)
      rays->horizontal.dist = __FLT_MAX__;
    else
      rays->horizontal.dist =
          ft_distance_between_2_points(cub->player.pos, cub->rayend_h);

    if (rays->horizontal.dist < rays->vertical.dist && rays->horizontal.dist > 0.0) {
      rays->shortest = &rays->horizontal;
//      hit = cub->rayend_h;
    } else {
      rays->shortest = &rays->vertical;
//      hit = cub->rayend_v;
    }
    // ft_line(cub->img, cub->player.pos, rays->shortest->end, \
		// 	rays->shortest->colour);
    ft_draw_ray(cub);
    rays->ray_angle =
        ft_fix_angle(rays->ray_angle - (1.0 * (60.0 / cub->mlx->width)));
  }
}
