/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:47:02 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:47:04 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*new;

	new = NULL;
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (0);
	if (content == NULL)
		new->content = NULL;
	else
		new->content = content;
	new->next = NULL;
	return (new);
}
