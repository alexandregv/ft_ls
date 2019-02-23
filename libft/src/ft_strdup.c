/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:54:54 by aguiot--          #+#    #+#             */
/*   Updated: 2018/12/14 13:08:36 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char *s2;

	if ((s2 = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)) == NULL)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}
