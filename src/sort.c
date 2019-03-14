#include "libft.h"
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
