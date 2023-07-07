/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:47:12 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:47:14 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		count;

	if (!lst)
		return (0);
	tmp = lst;
	count = 0;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
