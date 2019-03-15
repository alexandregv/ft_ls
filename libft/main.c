/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:14:21 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/15 15:04:13 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char	*str;

	str = ft_smartalloc(2);
	str[0] = '1';
	str[1] = '\0';

	str = ft_smartalloc(2);
	str[0] = '2';
	str[1] = '\0';

	str = ft_smartalloc(2);
	str[0] = '3';
	str[1] = '\0';

	ft_putendl(str);
	ft_smartfree();
	while (1);
}
