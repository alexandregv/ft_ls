#include "ft_ls.h"

int		lstcmp(const t_list *node1, const t_list *node2)
{
	char		*fullpath1;
	char		*fullpath2;

	fullpath1 = ft_strjoin(((t_file *)node1->content)->path, ((t_file *)node1->content)->name);
	fullpath2 = ft_strjoin(((t_file *)node2->content)->path, ((t_file *)node2->content)->name);

	DEBUGstr(" => sorting ");
	DEBUGstr(fullpath1);
	DEBUGstr("	|	");
	DEBUGendl(fullpath2);
	//TODO: lol leaks
	return (ft_strcmp(fullpath1, fullpath2) <= 0);
}

void	del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
	(void)size;
}
