/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:05:50 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:20:19 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	fill_node(t_list *node, const void *content, size_t content_size, int copy)
{
	if (copy)
	{
		if ((node->content = ft_memalloc(content_size)) == NULL)
		{
			ft_memdel((void **)&node);
			return (-1);
		}
		ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
	}
	else
	{
		node->content = (void *)content;
		node->content_size = content_size;
	}
	return (0);
}

t_list
	*ft_list_new(const void *content, size_t content_size, int copy)
{
	t_list	*node;

	if ((node = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else if (fill_node(node, content, content_size, copy))
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
