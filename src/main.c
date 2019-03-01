#include <string.h>
#include <stdio.h>
#include "ft_ls.h"

void	print_dir(t_list *node)
{
	if ((g_flags.R) && S_ISDIR(((t_file *)node->content)->stat.st_mode))
	{
		ft_putendl(((t_file *)node->content)->name);
		ft_putchar('\n');
		ft_putstr(((t_file *)node->content)->path);
		ft_putstr(((t_file *)node->content)->name);
		ft_putendl(":");
	}
	else
		ft_putendl(((t_file *)node->content)->name);
	//if (g_flags.R && node->next != NULL && S_ISDIR(((t_file *)node->next->content)->stat.st_mode))
	//	ft_putchar('\n');
}

t_list	*ft_while(t_list *list, char *path)
{
	DIR			*dirp;
	t_dirent	*direntp;
	t_file		*new;
	char		*fullpath;
	t_stat		statb;

	stat(path, &statb); //TODO: add protect
	if (!S_ISDIR(statb.st_mode))
	{
		new = (t_file *)malloc(sizeof(t_file));
		ft_strcpy(new->name, path);
		ft_strcpy(new->path, path);
		ft_strcat(new->path, "/");
		lstat(path, &new->stat); //TODO: add protect
		ft_list_push_back(&list, ft_list_new(new, sizeof(t_file)));
		return (list);
	}
	dirp = opendir(path);
	if (dirp == NULL)
	{
		perror("ft_ls");
		exit(EXIT_FAILURE);
	}
	while ((direntp = readdir(dirp)))
	{
		DEBUGstr(direntp->d_name);
		DEBUGstr(" (path=");
		DEBUGstr(path);
		DEBUGstr(")");
		if ((g_flags.a)
			|| direntp->d_name[0] != '.'
			|| ((g_flags.A && ft_strcmp(direntp->d_name, ".")) != 0
				&& (g_flags.A && ft_strcmp(direntp->d_name, "..") != 0)))
		{
			DEBUGendl("");
			fullpath = ft_strjoin(path, "/");
			fullpath = ft_strjoin(fullpath, direntp->d_name);
			if ((g_flags.R) && direntp->d_type == DT_DIR)
			{
				DEBUGstr("-> Found subdirectory ");
				DEBUGstr(direntp->d_name);
				DEBUGstr(", launching ft_while on it (path=");
				DEBUGstr(fullpath);
				DEBUGendl(")");
				list = ft_while(list, fullpath);
				DEBUGstr("<- Quitting ft_while on ");
				DEBUGendl(direntp->d_name);
			}
			new = (t_file *)malloc(sizeof(t_file));
			ft_strcpy(new->name, direntp->d_name);
			ft_strcpy(new->path, path);
			ft_strcat(new->path, "/");
			lstat(fullpath, &new->stat); //TODO: add protect
			if (!list)
				list = ft_lstnew(new, sizeof(*new));
			else
				ft_list_push_back(&list, ft_list_new(new, sizeof(*new)));
		}
		else
			DEBUGendl("	(SKIP)");
	}
	closedir(dirp);
	DEBUGendl("Closed dirp");
	return (list);
}

int		ls(int fc, char **fv)
{
	int			i;
	t_list		*args;
	t_list		*list;

	list = NULL;
	if (fc == 0)
	{
		fc = 1;
		fv = (char *[]) {".", NULL};
	}
	args = sort_args(fv);
	i = 0;
	while (i < fc && args)
	{
		if (fc >= 2 || (g_flags.R))
		{
			if (S_ISDIR(args->content_size))
			{
				if (i != 0)
					ft_putchar('\n');
				//ft_putstr(args->content);
				//ft_putendl(":");
			}
		}
		DEBUGstr("Starting path = ");
		DEBUGendl(args->content);
		list = ft_while(list, args->content);
		if (list)
		{
			if (!g_flags.U)
			{
				//ft_list_sort(&list, &lstcmp);
				ft_list_msort(&list);
				if (g_flags.r)
					ft_list_rev(&list); //TODO: remplacer par un sort < 0
			}
			DEBUGendl("----------------------------");
			//ft_list_iter(list, print_dir);
				//???
				t_file *db = (t_file *)malloc(sizeof(t_file));
				ft_strcpy(db->path, (char *)args->content);
				ft_strcpy(db->name, "");
				ft_list_push_front(&list, ft_list_new(db, sizeof(t_file)));
			//DEBUG(ft_list_iter(list, print_node));
			print_all(list, fc);
			++i;
			ft_list_del(&list, NULL);
		}
		args = args->next;
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int			flags_count;

	flags_count = parse_flags(ac, av);
	if (flags_count == -1)
		return (0);
	DEBUG(debug_flags(flags_count));
	return (ls(ac - flags_count, av + flags_count));
}
