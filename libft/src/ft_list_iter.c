/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:09:41 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:09:51 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_iter(t_list *head, void (*f)(t_list *elem))
{
	t_list	*node;

	node = head;
	while (node)
	{
		f(node);
		node = node->next;
	}
}
