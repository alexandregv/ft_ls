/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_get_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:06:28 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:06:42 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_get_at(t_list *head, size_t index)
{
	t_list	*node;

	node = head;
	while (index > 0 && node->next)
	{
		node = node->next;
		--index;
	}
	if (index > 0)
		return (NULL);
	return (node);
}
