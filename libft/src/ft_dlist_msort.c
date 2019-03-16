/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_msort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:17:08 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:17:09 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list
	*merge(t_list *first, t_list *second, int (*cmp)(t_list *, t_list *))
{
	if (!first)
		return (second);
	if (!second)
		return (first);
	if (cmp(first, second))
	{
		first->next = merge(first->next, second, cmp);
		first->next->prev = first;
		first->prev = NULL;
		return (first);
	}
	else
	{
		second->next = merge(first, second->next, cmp);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
}

static t_list
	*split(t_list *head)
{
	t_list *fast;
	t_list *slow;
	t_list *temp;

	fast = head;
	slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	temp = slow->next;
	slow->next = NULL;
	return (temp);
}

t_list
	*ft_dlist_msort(t_list *head, int (*cmp)(t_list *, t_list *))
{
	t_list	*second;

	if (!head || !head->next)
		return (head);
	second = split(head);
	head = ft_dlist_msort(head, cmp);
	second = ft_dlist_msort(second, cmp);
	return (merge(head, second, cmp));
}
