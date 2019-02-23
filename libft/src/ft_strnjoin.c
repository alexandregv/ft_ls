/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:23:47 by aguiot--          #+#    #+#             */
/*   Updated: 2018/12/14 12:51:11 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*cat;

	if (!s1 || !s2)
		return (NULL);
	if ((cat = ft_strnew(ft_strlen(s1) + n)) == NULL)
		return (NULL);
	cat = ft_strncat(ft_strcat(cat, s1), s2, n);
	return (cat);
}
