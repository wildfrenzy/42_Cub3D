/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:51:46 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 17:23:38 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	findlen;
	size_t	counter;

	findlen = ft_strlen(s2);
	if (findlen == 0)
		return ((char *)s1);
	counter = 0;
	while (*s1 && counter < n)
	{
		i = 0;
		while (s1[i] == s2[i] && counter + i < n)
		{
			if (s2[i + 1] == '\0')
				return ((char *)s1);
			i++;
		}
		s1++;
		counter++;
	}
	return (0);
}
