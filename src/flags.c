#include "ft_ls.h"

int		parse_flags(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && av[i][0] == '-' && av[i][1] != '\0' && av[i][1] != '-')
	{
		++av[i];
		while (*av[i])
		{
			if (*av[i] == 'l')
				g_flags.l = 1;
			else if (*av[i] == 'R')
				g_flags.R = 1;
			else if (*av[i] == 'a')
			{
				g_flags.A = 0;
				g_flags.a = 1;
			}
			else if (*av[i] == 'A')
			{
				g_flags.a = 0;
				g_flags.A = 1;
			}
			else if (*av[i] == 'r')
				g_flags.r = 1;
			else if (*av[i] == 't')
				g_flags.t = 1;
			else if (*av[i] == 'U')
				g_flags.U = 1;
			else if (*av[i] == 'G')
				g_flags.G = 1;
			else
			{
				ft_putstr("ft_ls: invalid option -- '");
				ft_putchar(*av[i]);
				ft_putendl("'");
				return (-1);
			}
			++av[i];
		}
		++i;
	}
	if (av[i] && !ft_strcmp(av[i], "--"))
		++i;
	return (i);
}
