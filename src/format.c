#include "ft_ls.h"

void		align(char *str, size_t max, char **ptr)
{
	int		spaces;

	spaces = max - ft_strlen(str);
	while (spaces-- > 0)
		*(*ptr)++ = ' ';
}

static void	print_time(t_stat statb, char **ptr)
{
	char	*temps;
	time_t	now;

	temps = ctime(&statb.ST_MTIME);
	time(&now);
	if ((now - statb.ST_MTIME) >= 15552000)
	{
		temps += 4;
		**ptr = '\0';
		ft_strncat(*ptr, temps, 7);
		*ptr += 7;
		**ptr = '\0';
		ft_strncat(*ptr, " ", 1);
		*ptr += 1;
		temps += 16;
		**ptr = '\0';
		ft_strncat(*ptr, temps, 4);
		*ptr += 4;
	}
	else
	{
		temps += 4;
		**ptr = '\0';
		ft_strncat(*ptr, temps, 12);
		*ptr += 12;
	}
}

static void	print_size(t_stat statb, size_t *max, char **ptr)
{
	char	*size;

	if (S_ISCHR(statb.st_mode) || S_ISBLK(statb.st_mode)) //TODO: buff et i
	{
		size = ft_itoa(major(statb.st_rdev));
		align(size, max[0], ptr);
		**ptr = '\0';
		ft_strcat(*ptr, size);
		*ptr += ft_strlen(size);
		free(size);
		**ptr = '\0';
		ft_strcat(*ptr, ", ");
		*ptr += 2;
		size = ft_itoa(minor(statb.st_rdev));
		align(size, max[1], ptr);
		**ptr = '\0';
		ft_strcat(*ptr, size);
		*ptr += ft_strlen(size);
		free(size);
	}
	else
	{
		size = ft_itoa(statb.st_size);
		align(size, max[0] + max[1] + (max[1] == 0 ? SIZE_SEPARATOR : 1), ptr);
		**ptr = '\0';
		ft_strcat(*ptr, size);
		*ptr += ft_strlen(size);
		free(size);
	}
}

void		print_file(t_list *node, size_t *tab)
{
	char	buff[NAME_MAX + 1024 + 1];
	ft_memset(buff, ' ', NAME_MAX + 1024);
	buff[NAME_MAX + 1024] = '\0';
	char	*ptr;
	char	*links;

	ptr = buff;
	if (g_flags.l)
	{
		print_filemodes(node, &ptr);
		*ptr++ = ' ';

		links = ft_itoa(f(node)->stat.st_nlink);
		align(links, tab[1], &ptr);
		*ptr = '\0';
		strcat(ptr, links);
		ptr += ft_strlen(links);
		*ptr++ = ' ';

		print_fileowner(f(node)->stat, tab[2], &ptr);
		*ptr = '\0';
		ft_strcat(ptr, OWNER_GROUP_SEPARATOR);
		ptr += ft_strlen(OWNER_GROUP_SEPARATOR);

		print_filegroup(f(node)->stat, tab[3], &ptr);
		*ptr++ = ' ';

		print_size(f(node)->stat, tab + 4, &ptr);
		*ptr++ = ' ';

		print_time(f(node)->stat, &ptr);
		*ptr++ = ' ';

		*ptr++ = '\0';
		ft_putstr(buff);
		free(links);
	}
	print_filename(f(node));
}
