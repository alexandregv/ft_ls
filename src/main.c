#include <string.h>
#include <stdio.h>
#include "ft_ls.h"

void	print_dir(t_list *node)
{
	if ((g_flags.r_up) && S_ISDIR(((t_file *)node->content)->stat.st_mode))
	{
		ft_putendl(((t_file *)node->content)->name);
		ft_putchar('\n');
		ft_putstr(((t_file *)node->content)->path);
		ft_putstr(((t_file *)node->content)->name);
		ft_putendl(":");
	}
	else
		ft_putendl(((t_file *)node->content)->name);
}

t_list	*ft_while(t_list *list, char *path)
{
	DIR			*dirp;
	t_dirent	*direntp;
	t_file		*new;
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
		//exit(EXIT_FAILURE);
		return (list);
	}
	while ((direntp = readdir(dirp)))
	{
		DEBUGstr(direntp->d_name);
		DEBUGstr(" (path=");
		DEBUGstr(path);
		DEBUGstr(")");
		if ((g_flags.a)
			|| direntp->d_name[0] != '.'
			|| ((g_flags.a_up && ft_strcmp(direntp->d_name, ".")) != 0
				&& (g_flags.a_up && ft_strcmp(direntp->d_name, "..") != 0)))
		{

			DEBUGendl("");
			new = (t_file *)malloc(sizeof(t_file));
			ft_strcpy(new->name, direntp->d_name);
			ft_strcpy(new->path, path);
			ft_strcat(new->path, "/");
			ft_strcpy(new->full_path, new->path);
			ft_strcat(new->full_path, new->name);
			lstat(new->full_path, &new->stat); //TODO: add protect
			if ((g_flags.r_up) && direntp->d_type == DT_DIR && ft_strcmp(direntp->d_name,".") != 0 && ft_strcmp(direntp->d_name,"..") != 0)
			{
				DEBUGstr("-> Found subdirectory ");
				DEBUGstr(direntp->d_name);
				DEBUGstr(", launching ft_while on it (path=");
				DEBUGstr(new->full_path);
				DEBUGendl(")");
				list = ft_while(list, new->full_path);
				DEBUGstr("<- Quitting ft_while on ");
				DEBUGendl(direntp->d_name);
			}
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
		if (fc >= 2 || (g_flags.r_up))
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
			if (!g_flags.u_up)
			{
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

				ft_strcpy(db->full_path, (char *)args->content);
				ft_strcat(db->full_path, "");
				
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
