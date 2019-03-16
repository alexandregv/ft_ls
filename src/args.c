#include "ft_ls.h"

static t_list	*norm_lol(t_list *files, t_list *dirs)
{
	if (!g_flags.u_up)
	{
		if (files != NULL)
			ft_list_sort(&files, (int (*)(const void*, const void*))ft_strcmp);
		if (dirs != NULL)
			ft_list_sort(&dirs, (int (*)(const void*, const void*))ft_strcmp);
	}
	if (!g_flags.u_up && g_flags.r)
	{
		if (files != NULL)
			ft_list_rev(&files);
		if (dirs != NULL)
			ft_list_rev(&dirs);
	}
	if (files != NULL)
	{
		ft_list_last(files)->next = dirs;
		DEBUG(ft_list_iter(files, print_node, 0));
		return (files);
	}
	else
	{
		DEBUG(ft_list_iter(dirs, print_node, 0));
		return (dirs);
	}
}

t_list			*sort_args(char **fv)
{
	t_list	*files;
	t_list	*dirs;
	t_stat	statb;
	t_list	*new;
	size_t	i;

	files = NULL;
	dirs = NULL;
	i = 0;
	while (fv[i])
	{
		if (stat(fv[i], &statb) != -1)
		{
			new = ft_list_new(NULL, 0, 0);
			new->content = ft_strdup(fv[i]);
			new->content_size = statb.st_mode;
			ft_list_push_back(S_ISDIR(statb.st_mode) ? &dirs : &files, new);
		}
		else
		{
			ft_putstr("ft_ls: '");
			ft_putstr(fv[i]);
			ft_putendl("': No such file or directory");
		}
		++i;
	}
	return (norm_lol(files, dirs));
}
