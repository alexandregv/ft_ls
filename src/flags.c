/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:54 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 21:04:44 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	invalid_option(char option)
{
	ft_putstr("ft_ls: invalid option -- '");
	ft_putchar(option);
	ft_putendl("'\nusage: ft_ls [-AFGRafgilrtu] [file ...]");
	return (-1);
}

static void	check_flm(char **av, int i)
{
	if (*av[i] == 'f')
	{
		g_flags.f = 1;
		g_flags.a = 1;
	}
	if (*av[i] == 'l')
	{
		g_flags.l = 1;
		g_flags.m = 0;
	}
	if (*av[i] == 'm')
	{
		g_flags.l = 0;
		g_flags.m = 1;
	}
	if (*av[i] == 'g')
	{
		g_flags.l = 1;
		g_flags.g = 1;
	}
}

static int	check_flags_chars(char **av, int i)
{
	g_flags.r_up = (*av[i] == 'R' ? 1 : g_flags.r_up);
	g_flags.r = (*av[i] == 'r' ? 1 : g_flags.r);
	g_flags.t = (*av[i] == 't' ? 1 : g_flags.t);
	g_flags.g_up = (*av[i] == 'G' ? 1 : g_flags.g_up);
	g_flags.i = (*av[i] == 'i' ? 1 : g_flags.i);
	g_flags.f_up = (*av[i] == 'F' ? 1 : g_flags.f_up);
	check_flm(av, i);
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
			&& *av[i] != 'f' && *av[i] != 'G' && *av[i] != 'g' && *av[i] != 'i'
			&& *av[i] != 'F' && *av[i] != 'm')
		return (invalid_option(*av[i]));
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
