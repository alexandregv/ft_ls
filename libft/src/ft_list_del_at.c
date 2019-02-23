/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:09:09 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:09:16 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_del_at(t_list **head, void (*del)(void *, size_t), size_t index)
{
	t_list	*node;

	node = ft_list_get_at(*head, index);
	ft_list_del_node(&node, del);
}
