#include "ft_ls.h"

int		lstcmp(const void *c1, const void *c2)
{
	char		*fullpath1;
	char		*fullpath2;

	fullpath1 = ft_strjoin(((t_file *)c1)->path, ((t_file *)c1)->name);
	fullpath2 = ft_strjoin(((t_file *)c2)->path, ((t_file *)c2)->name);

	DEBUGstr(" => sorting ");
	DEBUGstr(fullpath1);
	DEBUGstr("	|	");
	DEBUGendl(fullpath2);
	return (ft_strcmp(fullpath1, fullpath2));
	//return (ft_strcmp(((t_file *)c1)->name, ((t_file *)c2)->name));
	//return (ft_strcmp(((t_file *)c1)->path, ((t_file *)c2)->path));
}

void	del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
	(void)size;
}
