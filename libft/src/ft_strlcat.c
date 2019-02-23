/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:47:49 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/09 12:36:51 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	j = 0;
	i = ft_strlen(dst);
	res = ft_strlen(src) + (size <= i ? size : i);
	while (src[j] && i < (size - 1) && size != 0)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (res);
}
