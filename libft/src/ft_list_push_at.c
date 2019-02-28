/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:07:26 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/28 00:44:41 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_list_push_at(t_list **head, t_list *node, size_t index)
{
	t_list  *temp;

	if (index == 0)
	{
		if (*head == NULL)
			*head = node;
		else
		{
			node->next = *head;
			*head = node;
		}
	}
	else
	{
		temp = *head;
		while (--index > 0 && temp->next)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
	return (node);
}
