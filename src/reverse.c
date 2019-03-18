/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:20 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 13:54:51 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*fix_reverse_dirs(t_list *head)
{
	t_list	*node;
	t_list	*temp;

	node = head;
	while (node)
	{
		if (S_ISDIR(((t_file *)node->content)->stat.st_mode))
		{
			temp = node;
			while (temp->prev)
				if (ft_strncmp(f(node)->full_path, f(temp = temp->prev)->path
							, ft_strlen(f(node)->full_path)) != 0)
					break ;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = temp->next;
			temp->next->prev = node;
			temp->next = node;
			node->prev = temp;
		}
		node = node->next;
	}
	return (head);
}

void	handle_r(t_list **list, t_list *args)
{
	if (g_flags.r)
	{
		manual_add(list, args, 1);
		if (g_flags.r_up)
			*list = fix_reverse_dirs(*list);
	}
	else
		manual_add(list, args, 2);
}
