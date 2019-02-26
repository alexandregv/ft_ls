/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:08:06 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/25 20:44:47 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_list_push_back(t_list **node, t_list *new)
{
       return (ft_list_push_at(node, new, ft_list_size(*node)));
}

