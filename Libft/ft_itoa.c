/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:43:53 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:43:56 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	res;

	res = 0;
	if (n < 0 || n == 0)
		res = 1;
	while (n != 0)
	{
		res += 1;
		n /= 10;
	}
	return (res);
}

static void	helper(int numlen, char **num, int minus, int *n)
{
	numlen -= 1;
	while (numlen > 0)
	{
		if (minus)
			(*num)[numlen] = -(*n % 10) + 48;
		else
			(*num)[numlen] = (*n % 10) + 48;
		numlen--;
		*n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		numlen;
	int		minus;

	minus = 0;
	numlen = ft_numlen(n);
	num = malloc(numlen + 1);
	if (num == (void *)0)
		return ((void *)0);
	if (n < 0)
	{
		num[0] = '-';
		minus = 1;
	}
	num[numlen] = '\0';
	helper(numlen, &num, minus, &n);
	if (minus == 0)
		num[0] = n + 48;
	return (num);
}
