/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:47:55 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:47:57 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*as1;
	unsigned char	*as2;
	size_t			i;

	if (n == 0)
		return (s1);
	as1 = (unsigned char *)s1;
	as2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
		as1[i] = as2[i];
	return (as1);
}
