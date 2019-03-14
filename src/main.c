#include <string.h>
#include <stdio.h>
#include "ft_ls.h"

#include <stdio.h>
void	print_dir(t_list *node)
{
	/*
	printf("prev: %s%s | curr: %s%s | next: %s%s\n"
			, node->prev ? ((t_file *)node->prev->content)->path : "DEBUT"
			, node->prev ? ((t_file *)node->prev->content)->name : ""
			, ((t_file *)node->content)->path
			, ((t_file *)node->content)->name
			, node->next ? ((t_file *)node->next->content)->path : ""
			, node->next ? ((t_file *)node->next->content)->name : "FIN"
	);
	*/

	printf("%s%s\n", ((t_file *)node->content)->path, ((t_file *)node->content)->name);
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
			fullpath = ft_strjoin(path, "/");
			fullpath = ft_strjoin(fullpath, direntp->d_name);
			if ((g_flags.r_up) && direntp->d_type == DT_DIR
					&& ft_strcmp(direntp->d_name,".") != 0
					&& ft_strcmp(direntp->d_name,"..") != 0)
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

/*
void	fix_reverse_dirs(t_list **head)
{
	t_list	*node;
	t_list	*ref;
	char	*dirpath;

	node = *head;
	ref = NULL;
	dirpath = ((t_file *)node->content)->path;
	while (node->next && !ft_strcmp(dirpath, ((t_file *)node->next->content)->path))
		node = node->next;

	while (node)
	{
		ref = node;
		DEBUGstr("> DEBUG ref: ");
		DEBUGstr(((t_file *)node->content)->path);
		DEBUGstr(" ");
		DEBUGendl(((t_file *)node->content)->name);

		node = node->next;
		if (!node)
			return ;
		dirpath = ft_strdup(((t_file *)node->content)->path);
		dirpath[ft_strlen(dirpath) - 1] = '\0';
		while (node->next && ft_strcmp(dirpath, ft_strjoin(((t_file *)node->next->content)->path, ((t_file *)node->next->content)->name)) != 0)
			node = node->next;

		DEBUGstr("> DEBUG node: ");
		DEBUGstr(((t_file *)node->content)->path);
		DEBUGstr(" ");
		DEBUGendl(((t_file *)node->content)->name);

		t_list *to_move;
		//if (node->next)
		//{
		//	to_move = node->next;
		//	DEBUGstr("> DEBUG dir to move: ");
		//	DEBUGstr(((t_file *)to_move->content)->path);
		//	DEBUGstr(" ");
		//	DEBUGendl(((t_file *)to_move->content)->name);

		//	node->next = to_move->next;
		//	to_move->next = ref->next;
		//	ref->next = to_move;
		//}
		//else
		//{
		//	to_move = node;
		//}
		to_move = node->next;
		DEBUGstr("> DEBUG dir to move: ");
		DEBUGstr(((t_file *)to_move->content)->path);
		DEBUGstr(" ");
		DEBUGendl(((t_file *)to_move->content)->name);

		node->next = to_move->next;
		to_move->next = ref->next;
		ref->next = to_move;

		DEBUG(ft_list_iter(*head, print_dir, 0));
	}
}
*/

#include <stdio.h>
t_list	*fix_reverse_dirs(t_list *head)
{
	t_list	*node;
	t_list	*temp;

	node = head;
	while (node)
	{
		if (S_ISDIR(((t_file *)node->content)->stat.st_mode))
		{
			DEBUG(printf("> DEBUG dir to move: %s%s\n", ((t_file *)node->content)->path, ((t_file *)node->content)->name));
			char *fullpath = ft_strjoin(((t_file *)node->content)->path, ((t_file *)node->content)->name);
			DEBUG(printf("> DEBUG fullpath = [%s]\n", fullpath));
			temp = node;
			while (temp->prev)
			{
				temp = temp->prev;
				if (ft_strncmp(fullpath, ((t_file *)temp->content)->path, ft_strlen(fullpath)) != 0)
					break ;
			}
			DEBUG(printf("> DEBUG dir a inserer apres ce node: %s%s\n", ((t_file *)temp->content)->path, ((t_file *)temp->content)->name));
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = temp->next;
			temp->next->prev = node;
			temp->next = node;
			node->prev = temp;
		}
		node = node->next;
	}
	return (head);
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
		if ((fc >= 2 || (g_flags.r_up)) && S_ISDIR(args->content_size) && i != 0)
			ft_putchar('\n');
		DEBUGstr("Starting path = ");
		DEBUGendl(args->content);
		list = ft_while(list, args->content);
		if (list)
		{
			DEBUGendl("------------List before sort----------------");
			DEBUG(ft_list_iter(list, print_dir, 0));
			DEBUGendl("-----------Sorting-----------------");
			if (!g_flags.u_up)
			{
				list = ft_dlist_msort(list, lstcmp);
				if (g_flags.r)
					ft_dlist_rev(&list);
				DEBUGendl("------------List after sort----------------");
				DEBUG(ft_list_iter(list, print_dir, 0));
			}
			if (g_flags.r)
			{
				DEBUGendl("-----------List after manual add of 1st entry at back-----------------");
				ft_list_push_back(&list, ft_list_new((t_file *)malloc(sizeof(t_file)), sizeof(t_file)));
				ft_strcpy(((t_file *)ft_list_get_at(list, ft_list_size(list) - 1)->content)->path, (char *)args->content);
				ft_strcpy(((t_file *)ft_list_get_at(list, ft_list_size(list) - 1)->content)->name, "");
				DEBUG(ft_list_iter(list, print_dir, 0))

				DEBUGendl("-----------Fixdirs-----------------");
				list = fix_reverse_dirs(list);
				DEBUGendl("-----------List after fixdirs-----------------");
				DEBUG(ft_list_iter(list, print_dir, 0));
			
				DEBUGendl("-----------List after YOLO-----------------");
				ft_list_push_front(&list, ft_list_pop_back(&list));
				DEBUG(ft_list_iter(list, print_dir, 0));
			}
			else
			{
				DEBUGendl("-----------List after manual add of 1st entry at front-----------------");
				ft_list_push_front(&list, ft_list_new((t_file *)malloc(sizeof(t_file)), sizeof(t_file)));
				ft_strcpy(((t_file *)list->content)->path, (char *)args->content);
				ft_strcpy(((t_file *)list->content)->name, "");
				DEBUG(ft_list_iter(list, print_dir, 0));
			}
			DEBUGendl("------------Print all----------------");
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
