#include "libft.h"
#include "ft_ls.h"

int		lstcmp(t_list *node1, t_list *node2)
{
	char		*fullpath1;
	char		*fullpath2;

	//TODO: handle -r
	if (g_flags.t)
		return (((t_file *)node1->content)->stat.ST_MTIME
				> ((t_file *)node2->content)->stat.ST_MTIME);
	//else if (!g_flags.u_up && g_flags.r)
	else
	{
		fullpath1 = ft_strjoin(((t_file *)node1->content)->path, ((t_file *)node1->content)->name);
		fullpath2 = ft_strjoin(((t_file *)node2->content)->path, ((t_file *)node2->content)->name);
		DEBUGstr(" => sorting ");
		DEBUGstr(fullpath1);
		DEBUGstr("	|	");
		DEBUGendl(fullpath2);
		//TODO: lol leaks
		return (ft_strcmp(fullpath1, fullpath2) < 0);
	}
}
