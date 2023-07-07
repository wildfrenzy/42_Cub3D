/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:15 by nmaliare          #+#    #+#             */
/*   Updated: 2022/12/10 19:08:47 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_skipspaces(int a)
{
	if (a == '\t' || a == '\n' || a == '\v' || a == ' '
		|| a == '\f' || a == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	minus;

	num = 0;
	minus = 1;
	if (*str == '\0')
		return (0);
	while (ft_skipspaces(*str))
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - 48;
		str++;
	}
	return (num * minus);
}
