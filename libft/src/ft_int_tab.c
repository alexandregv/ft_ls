/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulaao <sboulaao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:16:12 by sboulaao          #+#    #+#             */
/*   Updated: 2019/03/14 18:01:02 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_int_tab(int size)
{
	int	i;
	int	*tab;

	i = 0;
	if (!(tab = malloc(sizeof(int) * size)))
		return (NULL);
	while (i < size)
		tab[i++] = 0;
	return (tab);
}
