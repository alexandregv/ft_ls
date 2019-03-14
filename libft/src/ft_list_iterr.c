/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iterr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:09:41 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/13 16:56:31 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_iterr(t_list *tail, void (*f)(t_list *elem))
{
	t_list	*node;

	node = tail;
	while (node)
	{
		f(node);
		node = node->prev;
	}
}
