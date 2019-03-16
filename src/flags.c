/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:54 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:19:59 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_flags_chars(char **av, int i)
{
	g_flags.l = (*av[i] == 'l' ? 1 : g_flags.l);
	g_flags.r_up = (*av[i] == 'R' ? 1 : g_flags.r_up);
	g_flags.r = (*av[i] == 'r' ? 1 : g_flags.r);
	g_flags.t = (*av[i] == 't' ? 1 : g_flags.t);
	g_flags.u_up = (*av[i] == 'U' ? 1 : g_flags.u_up);
	g_flags.g_up = (*av[i] == 'G' ? 1 : g_flags.g_up);
	if (*av[i] == 'a')
	{
		g_flags.a_up = 0;
		g_flags.a = 1;
	}
	else if (*av[i] == 'A')
	{
		g_flags.a = 0;
		g_flags.a_up = 1;
	}
	else if (*av[i] != 'l' && *av[i] != 'R' && *av[i] != 'r' && *av[i] != 't'
			&& *av[i] != 'U' && *av[i] != 'G')
	{
		ft_putstr("ft_ls: invalid option -- '");
		ft_putchar(*av[i]);
		ft_putendl("'");
		return (-1);
	}
	return (0);
}

int			parse_flags(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0' && av[i][1] != '-')
	{
		++av[i];
		while (*av[i])
		{
			if (check_flags_chars(av, i) == -1)
				return (-1);
			++av[i];
		}
		++i;
	}
	if (av[i] && !ft_strcmp(av[i], "--"))
		++i;
	return (i);
}
