/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:08:33 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:08:46 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_del_node(t_list **node, void (*del)(void *, size_t))
{
	if (del)
		del((*node)->content, (*node)->content_size);
	free((*node)->content);
	(*node)->next = NULL;
	free(*node);
	*node = NULL;
}
