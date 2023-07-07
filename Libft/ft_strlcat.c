/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:52 by nmaliare          #+#    #+#             */
/*   Updated: 2022/12/10 19:19:13 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destlen;

	i = 0;
	destlen = ft_strlen(dest);
	if (destlen < size)
	{
		while (i < (size - destlen - 1) && src[i])
		{
			dest[destlen + i] = src[i];
			i++;
		}
		dest[destlen + i] = '\0';
	}
	if (size < destlen)
		return (size + ft_strlen((char *)src));
	else
		return (destlen + ft_strlen((char *)src));
}
