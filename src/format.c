#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include "ft_ls.h"

static void align(char *str, size_t max)
{
	int	spaces;

	spaces = max - ft_strlen(str);
	while (spaces-- > 0)
		ft_putchar(' ');
}

static void	print_filemodes(t_stat statb) //TODO: ACL + extended attr
{
	mode_t			mode;
	char			modes[11];

	mode = statb.st_mode;
	ft_memset(modes, '-', 10);
	modes[11] = '\0';

	if (S_ISDIR(mode))
		modes[0] = 'd';
	else if (S_ISCHR(mode))
		modes[0] = 'c';
	else if (S_ISBLK(mode))
		modes[0] = 'b';
	else if (S_ISLNK(mode))
		modes[0] = 'l';
	else if (S_ISSOCK(mode))
		modes[0] = 's';
	else if (S_ISFIFO(mode))
		modes[0] = 'p';

	modes[1] = mode & S_IRUSR ? 'r' : '-';
	modes[2] = mode & S_IWUSR ? 'w' : '-';
	modes[3] = mode & S_IXUSR ? 'x' : '-';
	modes[3] = mode & S_ISUID ? 's' : modes[3];

	modes[4] = mode & S_IRGRP ? 'r' : '-';
	modes[5] = mode & S_IWGRP ? 'w' : '-';
	modes[6] = mode & S_IXGRP ? 'x' : '-';
	modes[6] = mode & S_ISGID ? 's' : modes[6];

	modes[7] = mode & S_IROTH ? 'r' : '-';
	modes[8] = mode & S_IWOTH ? 'w' : '-';
	if ((mode & S_IXOTH) && !(mode & S_ISVTX))
		modes[9] = 'x';
	else if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		modes[9] = 'T';
	else if ((mode & S_IXOTH) && (mode & S_ISVTX))
		modes[9] = 't';
	ft_putstr(modes);
}

static void	print_fileowner(t_stat statb, size_t max)
{
	struct passwd	*pw;

	pw = getpwuid(statb.st_uid);
	if (pw != 0)
	{
		ft_putstr(pw->pw_name);
		align(pw->pw_name, max);
	}
}

static void	print_filegroup(t_stat statb, size_t max)
{
	struct group	*gr;

	gr = getgrgid(statb.st_gid);
	if (gr != 0)
	{
		ft_putstr(gr->gr_name);
		align(gr->gr_name, max);
	}
}

static void	print_time(t_stat statb) //TODO: Fix +/- 6 months
{
	char	*time;

	time = ctime(&statb.ST_MTIME);
	time += 4;
	//ft_putstr(time);
	write(1, time, 12);
}

#include <sys/sysmacros.h>
static void	print_size(t_stat statb, size_t max1, size_t max2) //TODO: Fix (rounds and units)
{
	char	*size;

	if (S_ISCHR(statb.st_mode) || S_ISBLK(statb.st_mode))
	{
		//align(ft_itoa(statb.st_rdev >> 8), max1);
		align(ft_itoa(major(statb.st_rdev)), max1 - 1);

		//ft_putnbr(statb.st_rdev >> 8);
		ft_putnbr(major(statb.st_rdev));

		ft_putstr(", ");

		//align(ft_itoa(statb.st_rdev & ((1U << 8) - 1)), max2);
		align(ft_itoa(minor(statb.st_rdev)), max2);

		//ft_putnbr(statb.st_rdev & ((1U << 8) - 1));
		ft_putnbr(minor(statb.st_rdev));
	}
	else
	{
		size = ft_itoa(statb.st_size);
		//align(size, max1);
		align(size, max1 + max2 + (max2 == 0 ? 0 : 1));
		ft_putstr(size);
	}
}

void	print_file(t_list *node, size_t *tab)
{
	if (g_flags.l)
	{
		//ft_putnbr(tab[5]);

		print_filemodes(((t_file *)node->content)->stat); //TODO: ACL + extended attr
		align(ft_itoa(((t_file *)node->content)->stat.st_nlink), tab[1]);
		ft_putchar(' ');
		ft_putnbr(((t_file *)node->content)->stat.st_nlink);
		ft_putchar(' ');
		print_fileowner(((t_file *)node->content)->stat, tab[2]);
		ft_putchar(' ');
		print_filegroup(((t_file *)node->content)->stat, tab[3]);
		ft_putchar(' ');
		print_size(((t_file *)node->content)->stat, tab[4], tab[5]); //TODO: Fix (rounds and units)
		ft_putchar(' ');
		print_time(((t_file *)node->content)->stat); //TODO: Fix +/- 6 months
		ft_putchar(' ');
	}
	print_filename((t_file *)node->content);
}
