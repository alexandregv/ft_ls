/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_get_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:06:49 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:16:22 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_list_get_index(t_list *head, t_list *node)
{
	t_list	*temp;
	ssize_t	index;

	index = 0;
	temp = head;
	while (temp)
	{
		if (temp == node)
			return (index);
		temp = temp->next;
		++index;
	}
	return (-1);
}
