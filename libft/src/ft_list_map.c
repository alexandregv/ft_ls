/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:09:57 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 18:10:04 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_map(t_list *head, t_list *(*f)(t_list *node))
{
	t_list	*mapped;

	if (head)
	{
		mapped = f(head);
		mapped->next = ft_list_map(head->next, f);
		return (mapped);
	}
	return (NULL);
}
