/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:15:52 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/20 16:50:28 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_error(int stat)
{
	write(2, "Error\n", 7);
	if (stat)
		write(2, ":)\n", 7);
	return (1);
}

int	ft_clean_exit(int stat, t_cub *cub)
{
	if (stat > 1)
		mlx_close_window(cub->mlx);
	if (stat > 2)
		free(cub->img);
	return (stat);
}