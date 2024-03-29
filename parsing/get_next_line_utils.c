/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 00:20:35 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:58:26 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gft_strchr(char *s, int c)
{
	unsigned char	a;

	a = (unsigned char)c;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == a)
			return (s);
		s++;
	}
	if (*s == a)
		return (s);
	return ((void *)0);
}

static char	*ft_salloc(size_t nelem)
{
	char	*arr;

	arr = malloc(nelem);
	if (!arr)
		return (NULL);
	arr[0] = '\0';
	return (arr);
}

char	*ft_new_content(char *content)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!content[i])
	{
		free(content);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (gft_strlen(content) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (content[i])
		str[j++] = content[i++];
	str[j] = '\0';
	free(content);
	return (str);
}

char	*gft_strjoin(char *content, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!buff)
		return (NULL);
	if (!content)
	{
		content = ft_salloc(1);
		if (!content)
			return (NULL);
	}
	str = malloc(sizeof(char) * ((gft_strlen(content) + gft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (content)
		while (content[++i] != '\0')
			str[i] = content[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[gft_strlen(content) + gft_strlen(buff)] = '\0';
	free(content);
	return (str);
}
