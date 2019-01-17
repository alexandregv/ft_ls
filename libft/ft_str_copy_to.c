/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_copy_to.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:51:22 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/26 18:57:44 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			ft_str_copy_to(char **dst, char *src, char c)
{
	char	*p;
	int		i;
	int		count;
	int		pos;

	i = -1;
	count = 0;
	while (src[++i])
		if (src[i] == c)
			break ;
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[count] && count < i)
	{
		p = *dst;
		*dst = ft_strnjoin(*dst, &src[count], 1);
		ft_memdel((void**)&p);
		if (*dst == NULL)
			return (0);
		count++;
	}
	return (pos);
}
