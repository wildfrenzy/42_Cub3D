/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 23:26:42 by nmaliare          #+#    #+#             */
/*   Updated: 2022/12/11 19:07:30 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_char(char *set, char s)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	move(size_t *len, size_t *i, char *s1, char *set)
{
	while (*len != 0 && s1[*i] && *i < *len)
	{
		if (is_char(set, s1[*i]))
			*(i) += 1;
		if (is_char(set, s1[*len - 1]))
			*(len) -= 1;
		else if (!is_char(set, s1[*i]) && !is_char(set, s1[*len - 1]))
			break ;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*str;
	char	*pstr;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	move(&len, &i, (char *)s1, (char *)set);
	str = malloc (len - i + 1);
	if (!str)
		return (NULL);
	pstr = str;
	while (i < len)
		*(str)++ = s1[i++];
	*str = '\0';
	return (pstr);
}
