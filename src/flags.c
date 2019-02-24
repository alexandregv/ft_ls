#include "ft_ls.h"

int		parse_flags(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		++av[i];
		while (*av[i])
		{
			if (*av[i] == 'l')
				g_flags.l = 1;
			if (*av[i] == 'R')
				g_flags.R = 1;
			if (*av[i] == 'a')
				g_flags.a = 1;
			if (*av[i] == 'r')
				g_flags.r = 1;
			if (*av[i] == 't')
				g_flags.t = 1;
			if (*av[i] == 'U')
				g_flags.U = 1;
			++av[i];
		}
		++i;
	}
	return (i);
}
