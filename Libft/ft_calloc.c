/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:41:53 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:41:56 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*arr;

	arr = malloc(nelem * elsize);
	if (!arr)
		return (NULL);
	ft_memset(arr, '\0', nelem * elsize);
	return (arr);
}
