/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:06:11 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:16:13 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_list_size(t_list *head)
{
	t_list	*temp;
	size_t	size;

	size = 0;
	temp = head;
	while (temp)
	{
		temp = temp->next;
		++size;
	}
	return (size);
}
