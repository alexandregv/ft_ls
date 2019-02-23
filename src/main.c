#include <string.h>
#include <stdio.h>

#include "../include/ft_ls.h"

#define OPT_l options[0]
#define OPT_R options[1]
#define OPT_a options[2]
#define OPT_r options[3]
#define OPT_t options[4]
#define OPT_U options[5]
#define OPTIONS_COUNT 6

int debug = 1;
#define DEBUGstr(x) if (debug) ft_putstr(x);
#define DEBUGendl(x) if (debug) ft_putendl(x);
int options[5];

int		lstcmp(const void *c1, const void *c2) 
{
	char	*tmppath1;
	char	*tmppath2;
	
	tmppath1 = ft_strjoin(((t_file *)c1)->path, ((t_file *)c1)->name);
	tmppath2 = ft_strjoin(((t_file *)c2)->path, ((t_file *)c2)->name);

	DEBUGstr(" => soooorting ");
	DEBUGstr(tmppath1);
	DEBUGstr(" | ");
	DEBUGendl(tmppath2);
	return (ft_strcmp(tmppath1, tmppath2));
	//return (ft_strcmp(((t_file *)c1)->name, ((t_file *)c2)->name));
	//return (ft_strcmp(((t_file *)c1)->path, ((t_file *)c2)->path));
}

int		parse_options(int ac, char **av, int *options)
{
	int				i;

	i = 0;
	while (i < OPTIONS_COUNT)
		options[i++] = 0;
	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		++av[i];
		while (*av[i])
		{
			OPT_l = (*av[i] == 'l') ? 1 : OPT_l;
			OPT_R = (*av[i] == 'R') ? 1 : OPT_R;
			OPT_a = (*av[i] == 'a') ? 1 : OPT_a;
			OPT_r = (*av[i] == 'r') ? 1 : OPT_r;
			OPT_t = (*av[i] == 't') ? 1 : OPT_t;
			OPT_U = (*av[i] == 'U') ? 1 : OPT_U;
			++av[i];
		}
		++i;
	}
	return (i);
}

void				debug_options(int *options, int i)
{
	ft_putstr(" R:");
	ft_putnbr(OPT_R);
	ft_putstr(" l:");
	ft_putnbr(OPT_l);
	ft_putstr(" a:");
	ft_putnbr(OPT_a);
	ft_putstr(" r:");
	ft_putnbr(OPT_r);
	ft_putstr(" t:");
	ft_putnbr(OPT_t);
	ft_putstr(" U:");
	ft_putnbr(OPT_U);
	ft_putchar('\n');
	ft_putstr(" i:");

	ft_putnbr(i);
	ft_putchar('\n');
	ft_putchar('\n');
}

int			count_dirs(char *path, int *options)
{
	int						count;
	DIR						*dirp;
	struct dirent	*direntp;

	count = 0;
	dirp = opendir(path);
	while ((direntp = readdir(dirp)))
		if (OPT_a || (!OPT_a && direntp->d_name[0] != '.'))
			++count;
	(void)options;
	return (count);
}

void	print_dir(t_list *node)
{
	DEBUGstr("[");
	DEBUGstr((char const *)(((t_file *)node->content))->name);
	DEBUGendl("]");
	if (OPT_R && S_ISDIR(((t_file *)node->content)->stat.st_mode))
	{
		ft_putendl((char const *)(((t_file *)node->content))->name);
		ft_putchar('\n');
		ft_putstr( (char const *)(((t_file *)node->content))->path);
		ft_putstr((char const *)(((t_file *)node->content))->name);
		ft_putendl(":");
	}
	else
		ft_putendl((char const *)(((t_file *)node->content))->name);
	//if (OPT_R && node->next != NULL && S_ISDIR(((t_file *)node->next->content)->stat.st_mode))
	//	ft_putchar('\n');
}

void	del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
	(void)size;
}

char	*ft_get_path(char *filename)
{
	t_stat	statb;
	size_t	i;
	char	*path;

	i = 0;
	stat(filename, &statb);
	if (1==1 && S_ISDIR(statb.st_mode))
		return (filename);
	//else if (S_ISDIR(statb->st_mode))
	else
	{
		while(filename[i])
			++i;
		while(i > 0 && filename[i] != '/')
			--i;
		if (i == 0)
			path = ft_strdup(".");
		else
			path = ft_strndup(filename, i);
		return (path);
	}
}

t_list	*ft_while(t_list *list, char *path, int *options)
{
	DIR				*dirp;
	struct dirent	*direntp;
	t_file 			*new;
	char			*tmppath;
	struct stat		statb;

	stat(path, &statb);
  	if (!S_ISDIR(statb.st_mode))
	{
		new = (t_file *)malloc(sizeof(t_file));
		ft_strcpy(new->name, path);
		if (!list)
			list = ft_lstnew(new, sizeof(*new));
		else
			ft_list_push_back(list, ft_list_new(new, sizeof(*new)));
		return (list);
	}
	dirp = opendir(path);	
	//if (dirp == NULL)
	//{
	//	perror("ft_ls");
	//	exit(EXIT_FAILURE);
	//}
	while ((direntp = readdir(dirp)))
	{
		DEBUGstr("Just readdired and got ");
		DEBUGstr(direntp->d_name);
		DEBUGstr(" (path=");
		DEBUGstr(path);
		DEBUGstr(")");
		if (OPT_a || direntp->d_name[0] != '.')
		{
			DEBUGendl("");
			tmppath = ft_strjoin(path, "/");
			tmppath = ft_strjoin(tmppath, direntp->d_name);
			if (OPT_R && direntp->d_type == DT_DIR)
			{
				DEBUGstr("-> Found subdirectory ");
				DEBUGstr(direntp->d_name);
				DEBUGstr(", launching ft_while on it (path=");
				DEBUGstr(tmppath);
				DEBUGendl(")");
				list = ft_while(list, tmppath, options);
				DEBUGstr("<- Quitting ft_while on ");
				DEBUGendl(direntp->d_name);
			}
			new = (t_file *)malloc(sizeof(t_file));
			ft_strcpy(new->name, direntp->d_name);
			ft_strcpy(new->path, path);
			ft_strcat(new->path, "/");
			lstat(tmppath, &new->stat); //add protect
			if (!list)
				list = ft_lstnew(new, sizeof(*new));
			else
				ft_list_push_back(list, ft_list_new(new, sizeof(*new)));
		}
		else
			DEBUGendl("	(SKIP)");
	}
	closedir(dirp);
	return (list);
}

static void	print_node(t_list *node)
{
	return ;
	write(1, " => ", 4);
	write(1, (char *)node->content, ft_strlen(node->content));
	write(1, "\n", 1);
}

t_list	*sort_fv(char **fv) //TODO: passer options pour meme pas register les ignores (genre .*)
{
	t_list	*files;
	t_list	*dirs;
	struct stat	statb;
	size_t	i;

	files = NULL;
	dirs = NULL;
	i = 0;
	while (fv[i])
	{
		stat(fv[i], &statb);
		if (S_ISDIR(statb.st_mode))
		{
			if (dirs == NULL)
				dirs = ft_list_new(ft_strdup(fv[i]), statb.st_mode);
			else
				ft_list_push_back(dirs, ft_list_new(ft_strdup(fv[i]), statb.st_mode));
		}
		else
		{
			if (files == NULL)
				files = ft_list_new(ft_strdup(fv[i]), statb.st_mode);
			else
				ft_list_push_back(files, ft_list_new(ft_strdup(fv[i]), statb.st_mode));
		}
		++i;
	}
	if (!OPT_U)
	{
		if (files != NULL)
			ft_list_sort(&files, (int (*)(const void *, const void *))ft_strcmp);
		if (dirs != NULL)
			ft_list_sort(&dirs, (int (*)(const void *, const void *))ft_strcmp);
	}
	if (files != NULL)
	{
		ft_list_get_at(files, ft_list_size(files) - 1)->next = dirs;
		ft_list_iter(files, print_node); //TODO: this is debug
		return (files);
	}
	else
	{
		ft_list_iter(dirs, print_node); //TODO: this is debug
		return (dirs);
	}
}


int		ls(int fc, char **fv, int *options)
{
	int			i;
	char		*path;
	t_list		*args;
	t_list		*list = NULL;

	if (fc == 0)
	{
		fc = 1;
		fv[0] = ".";
	}
	args = sort_fv(fv);
	i = 0;
	while (i < fc && args)
	{
		if (fc >= 2 || OPT_R)
		{
			if (S_ISDIR(args->content_size))
			{
				if (i != 0)
					ft_putchar('\n');
				ft_putstr(args->content);
				ft_putendl(":");
			}
		}
		path = ft_get_path(args->content);
		DEBUGstr("Starting path = ");
		DEBUGendl(path);
		list = ft_while(list, args->content, options);
		if (!OPT_U)
		{
			ft_list_sort(&list, &lstcmp);
			if (OPT_r)
				ft_list_rev(&list); //TODO: remplacer par un sort < 0 ?
		}
		DEBUGendl("----------------------------");
		//ft_putstr("total");ft_putnrr(42);
		ft_list_iter(list, print_dir);
		++i;
		ft_list_del(&list, NULL);
		args = args->next;
	}
	(void)options;
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	int	 i;
	//int				options[5];

	i = parse_options(ac, av, options);
	//debug_options(options, i);
	//ft_putendl(ft_get_path(av[1]));
	return(ls(ac-i, av+i, options));
}
