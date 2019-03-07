#include "ft_ls.h"

void		print_filename(t_file *file)
{
	char	buf[PATH_MAX + NAME_MAX];

	if (g_flags.G)
	{
		if (S_ISDIR(file->stat.st_mode))
			ft_putstr(COLOR_DIR);
		else if (S_ISLNK(file->stat.st_mode))
			ft_putstr(COLOR_LNK);
		else if (S_ISFIFO(file->stat.st_mode))
			ft_putstr(COLOR_FIFO);
		else if (S_ISSOCK(file->stat.st_mode))
			ft_putstr(COLOR_SOCK);
		else if (S_ISBLK(file->stat.st_mode))
			ft_putstr(COLOR_BLK);
		else if (S_ISCHR(file->stat.st_mode))
			ft_putstr(COLOR_CHR);
		else if (S_ISREG(file->stat.st_mode) && file->stat.st_mode & S_IXUSR)
			ft_putstr(COLOR_EXEC);
	}
	ft_putstr(file->name);
	if (g_flags.G)
		ft_putstr(COLOR_RESET);
	if (S_ISLNK(file->stat.st_mode))
	{
		ft_putstr(" -> ");
		write(1, buf, readlink(ft_strjoin(file->path, file->name), buf, PATH_MAX + NAME_MAX)); //TODO: protect + leak
	}
	ft_putchar('\n');
}

static void	print_summary(t_list *list, size_t *tab)
{
	char	*dirpath;

	dirpath = ft_strjoin(((t_file *)list->content)->path, ((t_file *)list->content)->name);
	dirpath = ft_strjoin(dirpath, "/");
	while (list)
	{
		if (!ft_strcmp(dirpath, ((t_file *)list->content)->path))
			print_file(list, tab);
		list = list->next;
	}
}

static void	print_dirs(t_list *list, int files_count)
{
	list = list->next;
	while (list)
	{
		if (S_ISDIR(((t_file *)list->content)->stat.st_mode))
			if (print_all(list, files_count))
				return ;
		list = list->next;
	}
}

size_t	*len_max(t_list *node)
{
	size_t	*tab;
	char	*dirpath;
	ssize_t	xattr;

	if(!(tab = malloc(sizeof(size_t) * 7)))
		return (NULL);
	//ft_memset(tab, 0, 6);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
	tab[6] = 0;
	dirpath = ft_strjoin(((t_file *)node->content)->path, ((t_file *)node->content)->name); //TODO: leaks
	dirpath = ft_strjoin(dirpath, "/");

	while (node)
	{
		if (!ft_strcmp(dirpath, ((t_file *)node->content)->path))
		{
			struct passwd	*pw;
			struct group	*gr;

			pw = getpwuid(((t_file *)node->content)->stat.st_uid);
			gr = getgrgid(((t_file *)node->content)->stat.st_gid);
			if (pw == 0 || gr == 0)
				return (NULL); //TODO: protect
			//TODO: tab[0] pour les perms
			if (ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_nlink)) > tab[1])
				tab[1] = ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_nlink));
			if (ft_strlen(pw->pw_name) > tab[2])
				tab[2] = ft_strlen(pw->pw_name);
			if (ft_strlen(gr->gr_name) > tab[3])
				tab[3] = ft_strlen(gr->gr_name);
			if (S_ISCHR(((t_file *)node->content)->stat.st_mode) || S_ISBLK(((t_file *)node->content)->stat.st_mode))
			{
				if (ft_strlen(ft_itoa(major(((t_file *)node->content)->stat.st_rdev))) > tab[4])
					tab[4] = ft_strlen(ft_itoa(major(((t_file *)node->content)->stat.st_rdev)));
				if (ft_strlen(ft_itoa(minor(((t_file *)node->content)->stat.st_rdev))) > tab[5])
					tab[5] = ft_strlen(ft_itoa(minor(((t_file *)node->content)->stat.st_rdev)));
			}
			else
				if (ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_size)) > tab[4])
					tab[4] = ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_size));
			if (!tab[6])
			{
				xattr = listxattr(ft_strjoin(((t_file *)node->content)->path, ((t_file *)node->content)->name), NULL, 0, XATTR_NOFOLLOW); //TODO: protect + leaks
				if (xattr >= 1)
					tab[6] = 1;
			}
		}
		node = node->next;
	}
	return (tab);
}

int	print_all(t_list *list, int files_count)
{
	t_list	*ptr;
	size_t	*tab;

	ptr = list;
	tab = NULL;
	if (*((t_file *)list->content)->name)
		ft_putchar('\n');
	if (g_flags.R || files_count > 1)
	{
		ft_putstr(((t_file *)list->content)->path);
		ft_putstr(((t_file *)list->content)->name);
		ft_putendl(":");
	}
	if (g_flags.l)
	{
		tab = len_max(list); //TODO: add protect
		ft_putstr("total ");
		ft_putnbr(count_blocks(list->next));
		ft_putchar('\n');
	}
	print_summary(list, tab);
	if (g_flags.R)
		print_dirs(list, files_count);
	if (list == ptr)
		return (1);
	return (0);
}
