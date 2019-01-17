/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:18:15 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:23:24 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char*)s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return (p);
		++p;
	}
	return (NULL);
}
