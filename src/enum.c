#include "../include/ft_ls.h"

//extern int	g_options;

int		parse_g_options(int ac, char **av)
{
	int				i;

	i = 0;
	while (i < ac && av[i][0] == '-')
	{
		++av[i];
		while (*av[i])
		{
			if (*av[i] == 'l')
				g_options |= OPT_l;
			if (*av[i] == 'R')
				g_options |= OPT_R;
			if (*av[i] == 'a')
				g_options |= OPT_a;
			if (*av[i] == 'r')
				g_options |= OPT_r;
			if (*av[i] == 't')
				g_options |= OPT_t;
			if (*av[i] == 'U')
				g_options |= OPT_U;
			++av[i];
		}
		++i;
	}
	return (i);
}
