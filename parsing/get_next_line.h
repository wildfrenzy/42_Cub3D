/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmacmaho <bmacmaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 00:09:57 by nmaliare          #+#    #+#             */
/*   Updated: 2023/07/07 17:56:19 by bmacmaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

//read
# include <unistd.h>

//malloc
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_new_content(char *content);
char	*gft_strjoin(char *content, char *buff);
size_t	gft_strlen(char *s);
char	*gft_strchr(char *s, int c);

#endif