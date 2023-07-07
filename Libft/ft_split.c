/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:49:50 by nmaliare          #+#    #+#             */
/*   Updated: 2022/12/09 00:14:08 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcounter(char const *s, char c)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			counter += 1;
		s++;
	}
	return (counter);
}

static int	wordlen(char const *s, char c)
{
	int	charcount;
	int	i;

	charcount = 0;
	i = -1;
	while (s[++i] != c && s[i])
		charcount++;
	return (charcount);
}

static char	*wordcopy(char **s, char c, int wlen)
{
	int		j;
	char	*neword;

	j = -1;
	neword = (char *)malloc(wlen + 1);
	if (!neword)
		return (0);
	while (++j < wlen && **s != c)
	{
		neword[j] = **s;
		(*s)++;
	}
	neword[j] = '\0';
	return (neword);
}

char	**ft_split(char const *s, char c)
{
	char	**newstr;
	int		count;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	count = wordcounter(s, c);
	newstr = (char **)malloc((count + 1) * sizeof(char *));
	if (!newstr)
		return (0);
	while (++i < count)
	{
		while (*s == c && *s)
			s++;
		newstr[i] = wordcopy((char **)&s, c, wordlen(s, c));
		if (!newstr[i])
		{
			while (newstr[--i] != 0)
				free(newstr[i]);
			return (0);
		}
	}
	newstr[i] = NULL;
	return (newstr);
}
