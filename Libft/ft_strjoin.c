/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:50:35 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:50:38 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	char	*arr;

	i = -1;
	k = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	arr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!arr)
		return (NULL);
	while (s1[++i])
		arr[i] = s1[i];
	i -= 1;
	while (s2[++k])
		arr[++i] = s2[k];
	arr[i + 1] = '\0';
	return (arr);
}
