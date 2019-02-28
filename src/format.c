#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include "ft_ls.h"

#ifndef S_ISVTX
# define S_ISVTX	 0001000
#endif
#ifndef S_ISTXT
# define S_ISTXT	 0001000
#endif

static char	*get_filemodes(struct stat statb)
{
	mode_t			mode;
	char			*modes;

	mode = statb.st_mode;
	modes = ft_strnew(11);

	modes[0] = S_ISDIR(mode) ? 'd' : '-'; //TODO: other types

	modes[1] = mode & S_IRUSR ? 'r' : '-';
	modes[2] = mode & S_IWUSR ? 'w' : '-';
	modes[3] = mode & S_IXUSR ? 'x' : '-';

	modes[4] = mode & S_IRGRP ? 'r' : '-';
	modes[5] = mode & S_IWGRP ? 'w' : '-';
	modes[6] = mode & S_IXGRP ? 'x' : '-';

	modes[7] = mode & S_IROTH ? 'r' : '-';
	modes[8] = mode & S_IWOTH ? 'w' : '-';
	if ((mode & S_IXOTH) && !(mode & S_ISTXT))
		modes[9] = 'x';
	else if (!(mode & S_IXOTH) && (mode & S_ISTXT))
		modes[9] = 'T';
	else if ((mode & S_IXOTH) && (mode & S_ISTXT))
		modes[9] = 't';
	else
		modes[9] = '-';
	return (modes);
}

static char	*get_fileowner(struct stat statb)
{
	struct passwd	*pw;

	pw = getpwuid(statb.st_uid);
	if (pw != 0)
		return (pw->pw_name);
	return (NULL);
}

static char	*get_filegroup(struct stat statb)
{
	struct group	*gr;

	gr = getgrgid(statb.st_gid);
	if (gr != 0)
		return (gr->gr_name);
	return (NULL);
}

static char	*get_mtime(struct stat statb)
{
#ifdef _DARWIN_FEATURE_64_BIT_INODE
	return(ctime(&statb.st_mtimespec.tv_sec));
#else
	return(ctime(&statb.st_mtime));
#endif
}

static void	print_time(char *time) //TODO: Fix +/- 6 months
{
	time += 4;
	write(1, time, 12);
}

static void	print_size(int size) //TODO: Fix (rounds and units)
{
	if (size < 1000)
		ft_putnbr(size);
	else
	{
		ft_putnbr(size / 1024.00);
		ft_putchar('.');
		ft_putnbr(size % 1024);
		ft_putchar('K');
	}
}

void	print_file(t_list *node)
{
	if (g_flags.l) //TODO: padding
	{
		ft_putstr(get_filemodes(((t_file *)node->content)->stat));
		ft_putchar(' ');
		ft_putnbr(((t_file *)node->content)->stat.st_nlink);
		ft_putchar(' ');
		ft_putstr(get_fileowner(((t_file *)node->content)->stat));
		ft_putchar(' ');
		ft_putstr(get_filegroup(((t_file *)node->content)->stat));
		ft_putchar(' ');
		print_size(((t_file *)node->content)->stat.st_size); //TODO: Fix (rounds and units)
		ft_putchar(' ');
		print_time(get_mtime(((t_file *)node->content)->stat)); //TODO: Fix +/- 6 months
		ft_putchar(' ');
	}
	ft_putendl(((t_file *)node->content)->name);
}
