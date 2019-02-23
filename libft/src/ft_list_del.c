/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:09:25 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:09:33 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_del(t_list **list, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		next = temp->next;
		ft_list_del_node(&temp, del);
		temp = next;
	}
	*list = NULL;
}
