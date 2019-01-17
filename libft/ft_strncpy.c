/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:13:07 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/21 15:09:28 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*d;

	if (!n)
		return (dst);
	d = dst;
	while (n && *src)
	{
		*dst++ = *src++;
		--n;
	}
	while (n--)
		*dst++ = '\0';
	return (d);
}
