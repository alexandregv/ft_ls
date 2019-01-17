/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:04:28 by aguiot--          #+#    #+#             */
/*   Updated: 2018/12/14 15:04:53 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		sizeof_split(char const *s, char c)
{
	char		*p;

	p = (char*)s;
	while (p && *p && *p != c)
		++p;
	return (p - s);
}

static int		count_splits(char const *s, char c)
{
	int			count;
	int			mode;

	mode = 0;
	count = 0;
	while (s && *s)
	{
		if (mode && *s == c)
			mode = 0;
		if (!mode && *s != c)
		{
			mode = 1;
			++count;
		}
		++s;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**arr;
	int			split_id;
	int			i;

	if (!s || !c)
		return (NULL);
	i = 0;
	split_id = count_splits((char const *)s, c);
	if ((arr = (char**)malloc(sizeof(char*)
					* (count_splits((char const *)s, c) + 1))) == NULL)
		return (NULL);
	while (split_id-- > 0)
	{
		while (s && *s && *s == c)
			++s;
		if ((arr[i] = ft_strsub((char const*)s, 0
						, sizeof_split((char const *)s, c))) == NULL)
			return (NULL);
		s += sizeof_split(s, c);
		++i;
	}
	arr[i] = 0;
	return (arr);
}
