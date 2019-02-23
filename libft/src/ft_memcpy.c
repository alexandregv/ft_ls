/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:56:41 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/13 13:24:14 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memcpy(void *dst, void const *src, size_t n)
{
	char	*pdst;
	char	*psrc;

	pdst = (char*)dst;
	psrc = (char*)src;
	while (n-- > 0)
		*(pdst++) = *(psrc++);
	return (dst);
}
