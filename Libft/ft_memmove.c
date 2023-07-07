/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:48:04 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:48:06 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = s1;
	ps = s2;
	if (ps < pd)
	{
		pd += n;
		ps += n;
		while (n--)
			*--pd = *--ps;
	}
	else
		while (n--)
			*pd++ = *ps++;
	return (s1);
}
