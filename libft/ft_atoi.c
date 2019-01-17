/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:04:38 by aguiot--          #+#    #+#             */
/*   Updated: 2018/11/19 18:22:30 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(char const *s)
{
	long long int	nb;
	long long int	k;

	nb = 0;
	while (s && *s && ft_isspace(*s))
		++s;
	k = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		++s;
	while (*s && ft_isdigit(*s))
		nb = (nb * 10) + (long long int)(*(s++) - 48);
	return (long long int)(nb * k);
}
