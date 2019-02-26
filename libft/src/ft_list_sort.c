/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:05:50 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/26 01:10:59 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_sort(t_list **head, int (*cmp)(const void *, const void *))
{
	void	*overflow;
	t_list	*temp;

	temp = *head;
	while ((*head)->next != NULL)
	{
		if ((cmp((*head)->content, (*head)->next->content)) > 0)
		{
			overflow = (*head)->content;
			(*head)->content = (*head)->next->content;
			(*head)->next->content = overflow;
			(*head) = temp;
		}
		else
			(*head) = (*head)->next;
	}
	*head = temp;
}
