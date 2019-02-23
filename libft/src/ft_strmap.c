/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:11:40 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/12 19:06:10 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*ptr;
	char	*ps;

	if (!s || (str = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	ptr = str;
	ps = (char*)s;
	while (ps && *ps)
		*(ptr++) = f(*(ps++));
	return (str);
}
