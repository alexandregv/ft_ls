/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_pop_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:07:26 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/18 17:05:39 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_pop_at(t_list **head, size_t index)
{
	t_list	*temp;
	t_list	*poped;

	if (index == 0)
	{
		poped = *head;
		*head = (*head)->next;
		poped->next = NULL;
		return (poped);
	}
	else
	{
		temp = *head;
		while (--index > 0 && temp->next)
			temp = temp->next;
		poped = temp->next;
		temp->next = poped->next;
		poped->next = NULL;
	}
	return (poped);
}
