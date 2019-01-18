#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include "../libft/libft.h"

#ifndef S_ISTXT
# define S_ISTXT	 0001000
#endif

static char		*get_filetype(struct stat statb)
{
	mode_t			mode;

	mode = statb.st_mode;
	if (S_ISREG(mode))
		return ("Fichier");
	else if (S_ISDIR(mode))
		return ("Dossier");
	else if (S_ISCHR(mode))
		return ("Char device");
	else if (S_ISBLK(mode))
		return ("Block device");
	else if (S_ISFIFO(mode))
		return ("FIFO");
	else if (S_ISSOCK(mode))
		return ("Socket");
	else if (S_ISLNK(mode))
		return ("Lien symbolique");
	return (NULL);
}

static char		*get_filemodes(struct stat statb)
{
	mode_t			mode;
	char				*modes;

	mode = statb.st_mode;
	modes = ft_strnew(11);

	modes[0] = S_ISDIR(mode) ? 'd' : '-';

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

	modes[10] = ' ';

	return (modes);
}

static char			*get_fileowner(struct stat statb)
{
	struct passwd	*pw;

	pw = getpwuid(statb.st_uid);
	if (pw != 0)
		return (pw->pw_name);
	return (NULL);
}

static char			*get_filegroup(struct stat statb)
{
	struct group	*gr;

	gr = getgrgid(statb.st_gid);
	if (gr != 0)
		return (gr->gr_name);
	return (NULL);
}

static char			*get_mtime(struct stat statb)
{
#ifdef _DARWIN_FEATURE_64_BIT_INODE
	return (ctime(&statb.st_mtimespec.tv_sec));
#else
	return (ctime(&statb.st_mtime));
#endif
}

static void			print_time(char *time)
{
	time += 4;
	write(1, time, 12);
}

static void		print_size(int size)
{
	if (size < 1000)
		ft_putnbr(size);
	else
	{
		int centaine = size / 100;
		if (size / (centaine * 100) >= 1.25)
			++centaine;

		ft_putnbr(size / 1024.00);
		ft_putchar('.');
		ft_putnbr(centaine / 100);
		//ft_putnbr(num < 0 ? num - 0.5 : num + 0.5);
		ft_putchar('K');
	}
}

int							mmain(int ac, char **av)
{
	struct stat	statb;

	if (ac != 2)
		ft_die("Usage: ./ft_inspect_file filename", 0);
	if (stat(av[1], &statb) < 0)
		ft_die("Error reading file attributes.", 1);

	ft_putstr("Nom: ");
	ft_putendl(av[1]);

	ft_putstr("Type: ");
	ft_putendl(get_filetype(statb));

	ft_putstr("Modes: ");
	ft_putendl(get_filemodes(statb));

	ft_putstr("Nombre de liens: ");
	ft_putnbr(statb.st_nlink);
	ft_putchar('\n');

	ft_putstr("Proprietaire: ");
	ft_putendl(get_fileowner(statb));

	ft_putstr("Groupe: ");
	ft_putendl(get_filegroup(statb));

	ft_putstr("Taille: ");
	ft_putnbr(statb.st_size);
	ft_putchar('\n');

	ft_putstr("Date de derniere modification: ");
	print_time(get_mtime(statb));
	ft_putchar('\n');

	ft_putchar('\n');
	ft_putstr(get_filemodes(statb));
	ft_putchar(' ');
	ft_putnbr(statb.st_nlink);
	ft_putchar(' ');
	ft_putstr(get_fileowner(statb));
	ft_putstr("  ");
	ft_putstr(get_filegroup(statb));
	ft_putstr("   ");
	print_size(statb.st_size);
	ft_putchar(' ');
	print_time(get_mtime(statb));
	ft_putchar(' ');
	ft_putendl(av[1]);

	return (0);
}
