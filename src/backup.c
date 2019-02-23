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

static void				ft_lstsort_swap(t_list *l1, t_list *l2)
{
	void				*tmp;
	size_t				size;

	tmp = l1->content;
	l1->content = l2->content;
	l2->content = tmp;
	size = l1->content_size;
	l1->content_size = l2->content_size;
	l2->content_size = size;
}

static inline t_list	*ft_lstsort_sorting(t_list *low, t_list *high, int (*f)(const void *, const void *))
{
	t_list				*tmp;
	t_list				*arrow;
	void				*median;

	tmp = low->next;
	arrow = low;
	median = low->content;
	while (tmp != high)
	{
		if (f((char *)tmp->content, (char *)median) < 0)
		{
			arrow = arrow->next;
			ft_lstsort_swap(tmp, arrow);
		}
		tmp = tmp->next;
	}
	ft_lstsort_swap(low, arrow);
	return (arrow);
}

static void				ft_lstsort_rec(t_list *low, t_list *high, int (*f)(const void *, const void *))
{
	t_list				*median;

	if (high == low)
		return ;
	median = ft_lstsort_sorting(low, high, f);
	ft_lstsort_rec(low, median, f);
	ft_lstsort_rec(median->next, high, f);
}

void					ft_lstsort(t_list *lst, int (*f)(const void *, const void *))
{
	ft_lstsort_rec(lst, NULL, f);
}

int	ft_lstcmp(const void *c1, const void *c2) 
{
	return (ft_strcmp(((t_file *)c1)->name, ((t_file *)c2)->name));
}

void		ft_lstrev(t_list **alst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	prev = NULL;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*alst = prev;
}

int					 parse_options(int ac, char **av, int *options)
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
	if (OPT_R && node->next != NULL && S_ISDIR(((t_file *)node->next->content)->stat.st_mode))
		ft_putchar('\n');
}

void	del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
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
			struct stat st;
			lstat(tmppath, &new->stat); //add protect
			if (!list)
				list = ft_lstnew(new, sizeof(*new));
			else
				ft_lstadd(&list, ft_lstnew(new, sizeof(*new)));
		}
		else
			DEBUGendl("	(SKIP)");
	}
	closedir(dirp);
	return (list);
}

int				ls(int fc, char **fv, int *options)
{
	int			i;
	char		*path;
	DIR			*dirp;
	t_list		*list = NULL;

	if (fc == 0)
	{
		fc = 1;
		fv[0] = ".";
	}
	i = 0;
	while (i < fc)
	{
		if (fc >= 2 || OPT_R)
		{
			if (i != 0)
				ft_putchar('\n');
			ft_putstr(fv[i]);
			ft_putendl(":");
		}
		path = ft_get_path(fv[i]);
		DEBUGstr("Starting path = ");
		DEBUGendl(path);
		list = ft_while(list, fv[i], options);
		ft_lstrev(&list);
		if (!OPT_U)
			ft_lstsort(list, &ft_lstcmp);
		DEBUGendl("----------------------------");
		//ft_putstr("total");ft_putnrr(42);
		ft_lstiter(list, print_dir);
		++i;
		ft_lstdel(&list, del_node);
		//list = NULL;
	}
	(void)options;
	return (EXIT_SUCCESS);
}

int					main(int ac, char **av)
{
	int	 i;
	//int				options[5];

	i = parse_options(ac, av, options);
	//debug_options(options, i);
	//ft_putendl(ft_get_path(av[1]));
	return(ls(ac-i, av+i, options));
}
