/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:54:09 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/14 12:52:16 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*temp;

	temp = *alst;
	while (temp)
	{
		next = temp->next;
		if (del)
			del(temp->content, temp->content_size);
		free(temp);
		temp = next;
	}
	*alst = NULL;
}
