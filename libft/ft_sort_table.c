/* ************************************************************************** */
/*																																						*/
/*																												:::			 ::::::::		*/
/*	 ft_sort_table.c																		:+:			 :+:		:+:		*/
/*																										+:+ +:+					+:+			*/
/*	 By: aguiot-- <aguiot--@student.42.fr>					+#+  +:+			 +#+				*/
/*																								+#+#+#+#+#+		+#+						*/
/*	 Created: 2019/01/22 15:38:29 by aguiot--					 #+#		#+#							*/
/*	 Updated: 2019/01/22 15:38:30 by aguiot--					###		########.fr				*/
/*																																						*/
/* ************************************************************************** */

#include "libft.h"

char			**ft_sort_table(char **table, size_t size)
{
	size_t	i;
	short		stop;
	char		*tmp;

	stop = 0;
	while (!stop)
	{
		stop = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(table[i], table[i + 1]) > 0)
			{
				tmp = table[i];
				table[i] = table[i + 1];
				table[i + 1] = tmp;
				stop = 0;
			}
			++i;
		}
	}
	return (table);
}
