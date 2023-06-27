/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:30:50 by barramacmah       #+#    #+#             */
/*   Updated: 2023/06/26 21:35:33 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_error(char *message)
{
	write(2, "Error\n", 7);
	write(2, message, ft_strlen(message));
	return (1);
}

int	check_file(char *file)
{
	//add ft_
	if (strncmp(file + strlen(file) - 4, ".cub", 4))
		return (1);
	return (0);
}

int	ft_errors(int argc, char **argv)
{
	if (argc != 2)
		return (ft_print_error("Wrong number of arguments\n"));
	if (check_file(argv[1]))
		return (ft_print_error("Invalid file extension\n"));
	return (0);
}