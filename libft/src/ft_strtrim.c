/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:44:57 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:30:47 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*trim;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		++i;
	j = ft_strlen(s) - 1;
	while (s[j] && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		--j;
	if (j == -1)
		i = 0;
	if ((trim = ft_strnew(j - i + 1)) == NULL)
		return (NULL);
	k = 0;
	while (i <= j)
		trim[k++] = s[i++];
	return (trim);
}
