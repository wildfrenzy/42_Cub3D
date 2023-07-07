/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:52:03 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:52:05 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	char			*a;

	ch = (unsigned char)c;
	if (!s || (*s == '\0' && ch != '\0'))
		return (NULL);
	a = (char *)s;
	while (*a)
		a++;
	if (ch == '\0')
		return (a);
	while (*--a)
	{
		if (*a == ch)
			return (a);
		else if (a == s)
			break ;
	}
	return (NULL);
}
