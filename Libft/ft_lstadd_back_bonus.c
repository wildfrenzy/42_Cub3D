/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmaliare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:25 by nmaliare          #+#    #+#             */
/*   Updated: 2022/11/28 15:44:28 by nmaliare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst)
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		*lst = new;
}
