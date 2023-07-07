/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:52:28 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:52:29 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;

	i = 0;
	a = NULL;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		a = malloc(1);
	else if (len >= ft_strlen(s))
		a = (char *)malloc(ft_strlen(s) - start + 1);
	else
		a = (char *)malloc(len + 1);
	if (!a)
		return (NULL);
	if (start < (unsigned int)ft_strlen(s))
	{
		while (i < len && s[start + i])
		{
			a[i] = s[start + i];
			i++;
		}
	}
	a[i] = '\0';
	return (a);
}
