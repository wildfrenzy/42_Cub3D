/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:02:10 by bmacmaho          #+#    #+#             */
/*   Updated: 2023/07/08 13:10:04 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_error(char *message)
{
	write(2, "Error\n", 7);
	write(2, message, ft_strlen(message));
	return (1);
}

int	ft_checkargs(int argc, char **argv)
{
	if (argc != 2)
		return (ft_print_error("Incorrect number of arguments\n"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
		return (ft_print_error("Invalid file extension\n"));
	return (0);
}
