#include "ft_ls.h"

int		lstcmp(t_list *node1, t_list *node2)
{
	if (g_flags.t)
	{
		if (g_flags.r)
			return (f(node1)->stat.ST_MTIME < f(node2)->stat.ST_MTIME);
		if (f(node1)->stat.ST_MTIME == f(node2)->stat.ST_MTIME)
			return (ft_strcmp(f(node1)->full_path, f(node2)->full_path) < 0);
		return (f(node1)->stat.ST_MTIME > f(node2)->stat.ST_MTIME);
	}
	else
	{
		DEBUGstr(" => sorting ");
		DEBUGstr(f(node1)->full_path);
		DEBUGstr("	|	");
		DEBUGstr(f(node2)->full_path);
		return (ft_strcmp(f(node1)->full_path, f(node2)->full_path) < 0);
	}
}

void	manual_add(t_list **list, t_list *args, int mode)
{
	if (mode == 1)
	{
		ft_list_push_back(list, ft_list_new((t_file *)malloc(sizeof(t_file))
					, sizeof(t_file)));
		ft_strcpy(f(ft_list_get_at(*list, ft_list_size(*list) - 1))->path
				, (char *)args->content);
		ft_strcpy(f(ft_list_get_at(*list, ft_list_size(*list) - 1))->name, "");
		ft_strcpy(f(ft_list_get_at(*list, ft_list_size(*list) - 1))->full_path
				, (char *)args->content);
		ft_strcat(f(ft_list_get_at(*list, ft_list_size(*list) - 1))->full_path
				, "");
	}
	else if (mode == 2)
	{
		ft_list_push_front(list, ft_list_new((t_file *)malloc(sizeof(t_file))
					, sizeof(t_file)));
		ft_strcpy(f(*list)->path, (char *)args->content);
		ft_strcpy(f(*list)->name, "");
		ft_strcpy(f(*list)->full_path, (char *)args->content);
		ft_strcpy(f(*list)->full_path, "");
	}
}

void	add_first_file(t_list **list, t_list *args)
{
	t_file	*first;

	first = (t_file *)malloc(sizeof(t_file));
	ft_strcpy(first->path, (char *)args->content);
	ft_strcpy(first->name, "");
	ft_strcpy(first->full_path, (char *)args->content);
	ft_strcat(first->full_path, "");
	ft_list_push_front(list, ft_list_new(first, sizeof(t_file)));
}
