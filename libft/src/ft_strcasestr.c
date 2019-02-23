/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:37:30 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:31:35 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strcasestr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		if (ft_tolower(haystack[i]) == ft_tolower(needle[0]))
		{
			j = 1;
			while (needle[j]
					&& ft_tolower(haystack[i + j]) == ft_tolower(needle[j]))
				++j;
			if (needle[j] == '\0')
				return ((char*)&haystack[i]);
		}
		++i;
	}
	return (0);
}
