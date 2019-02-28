#include "ft_ls.h"

static void	print_summary(t_list *list)
{
	char	*dirpath;

	dirpath = ft_strjoin(((t_file *)list->content)->path, ((t_file *)list->content)->name);
	dirpath = ft_strjoin(dirpath, "/");
	while (list)
	{
		if (!ft_strcmp(dirpath, ((t_file *)list->content)->path))
			print_file(list);
		list = list->next;
	}
}

static void	print_dirs(t_list *list)
{
	list = list->next;
	while (list)
	{
		if (S_ISDIR(((t_file *)list->content)->stat.st_mode))
			if (print_all(list))
				return ;
		list = list->next;
	}
}

int	print_all(t_list *list)
{
	t_list *ptr;
	ptr = list;

	if (*((t_file *)list->content)->name)
		ft_putchar('\n');
	ft_putstr(((t_file *)list->content)->path);
	ft_putstr(((t_file *)list->content)->name);
	ft_putendl(":");
	if (g_flags.l)
	{
		ft_putstr("total ");
		ft_putnbr(count_blocks(list->next));
		ft_putchar('\n');
	}
	print_summary(list);
	if (g_flags.R)
		print_dirs(list);
	if (list == ptr)
		return (1);
	return (0);
}
