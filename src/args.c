#include "ft_ls.h"

//TODO: check les flags pour ne pas register inutilement les ignores (genre .*)
t_list	*sort_args(char **fv)
{
	t_list		*files;
	t_list		*dirs;
	t_stat		statb;
	size_t		i;

	files = NULL;
	dirs = NULL;
	i = 0;
	while (fv[i])
	{
		stat(fv[i], &statb); //TODO: add protect
		if (S_ISDIR(statb.st_mode))
			ft_list_push_back(&dirs, ft_list_new(ft_strdup(fv[i]), statb.st_mode));
		else
			ft_list_push_back(&files, ft_list_new(ft_strdup(fv[i]), statb.st_mode));
		++i;
	}
	if (!g_flags.U)
	{
		if (files != NULL)
			ft_list_sort(&files, (int (*)(const void *, const void *))ft_strcmp);
		if (dirs != NULL)
			ft_list_sort(&dirs, (int (*)(const void *, const void *))ft_strcmp);
	}
	if (!g_flags.U && g_flags.r)
	{
		if (files != NULL)
			ft_list_rev(&files);
		if (dirs != NULL)
			ft_list_rev(&dirs);
	}
	if (files != NULL)
	{
		ft_list_get_at(files, ft_list_size(files) - 1)->next = dirs;
		DEBUG(ft_list_iter(files, print_node));
		return (files);
	}
	else
	{
		DEBUG(ft_list_iter(dirs, print_node));
		return (dirs);
	}
}


