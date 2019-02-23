/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:07:38 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/12 19:09:06 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	char	*ptr;
	char	*ps;
	int		i;

	if (!s || (str = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	ptr = str;
	ps = (char*)s;
	i = 0;
	while (ps && *ps)
		*(ptr++) = f(i++, *(ps++));
	return (str);
}
