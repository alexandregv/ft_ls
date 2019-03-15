#include "ft_ls.h"

void		align(char *str, size_t max)
{
	int		spaces;

	spaces = max - ft_strlen(str);
	while (spaces-- > 0)
		ft_putchar(' ');
}

static void	print_time(t_stat statb)
{
	char	*temps;
	time_t	now;

	temps = ctime(&statb.ST_MTIME);
	time(&now);
	if ((now - statb.ST_MTIME) >= 15552000)
	{
		temps += 4;
		write(1, temps, 7);
		write(1, " ", 1);
		temps += 16;
		write(1, temps, 4);
	}
	else
	{
		temps += 4;
		write(1, temps, 12);
	}
}

static void	print_size(t_stat statb, size_t max1, size_t max2)
{
	char	*size;

	if (S_ISCHR(statb.st_mode) || S_ISBLK(statb.st_mode))
	{
		size = ft_itoa(major(statb.st_rdev));
		align(size, max1);
		ft_putnbr(major(statb.st_rdev));
		ft_putstr(", ");
		free(size);
		size = ft_itoa(minor(statb.st_rdev));
		align(size, max2);
		ft_putnbr(minor(statb.st_rdev));
		free(size);
	}
	else
	{
		size = ft_itoa(statb.st_size);
		align(size, max1 + max2 + (max2 == 0 ? SIZE_SEPARATOR : 1));
		ft_putstr(size);
		free(size);
	}
}

void		print_file(t_list *node, size_t *tab)
{
	char	*links;

	if (g_flags.l)
	{
		links = ft_itoa(f(node)->stat.st_nlink);
		print_filemodes(node);
		align(links, tab[1]);
		ft_putchar(' ');
		ft_putnbr(f(node)->stat.st_nlink);
		ft_putchar(' ');
		print_fileowner(f(node)->stat, tab[2]);
		ft_putstr(OWNER_GROUP_SEPARATOR);
		print_filegroup(f(node)->stat, tab[3]);
		ft_putchar(' ');
		print_size(f(node)->stat, tab[4], tab[5]);
		ft_putchar(' ');
		print_time(f(node)->stat);
		ft_putchar(' ');
		free(links);
	}
	print_filename(f(node));
}
