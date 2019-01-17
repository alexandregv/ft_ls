/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:32:06 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:29:47 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(char const *s, int c)
{
	char	*last_c;

	last_c = NULL;
	while (*s)
	{
		if (*s == c)
			last_c = (char*)s;
		++s;
	}
	if (c == '\0')
		return ((char*)s);
	if (last_c == NULL)
		return (NULL);
	return ((char*)last_c);
}
