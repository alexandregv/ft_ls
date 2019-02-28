#include "ft_ls.h"

int		lstcmp(const t_list *node1, const t_list *node2)
{
	char		*fullpath1;
	char		*fullpath2;

	if (g_flags.t) //TODO: handle -r
	{
		return (((t_file *)node1->content)->stat.ST_MTIME > ((t_file *)node2->content)->stat.ST_MTIME);
	}
	else
	{
		fullpath1 = ft_strjoin(((t_file *)node1->content)->path, ((t_file *)node1->content)->name);
		fullpath2 = ft_strjoin(((t_file *)node2->content)->path, ((t_file *)node2->content)->name);

		DEBUGstr(" => sorting ");
		DEBUGstr(fullpath1);
		DEBUGstr("	|	");
		DEBUGendl(fullpath2);
		//TODO: lol leaks
		return (ft_strcmp(fullpath1, fullpath2) <= 0);
	}
}

void	del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
	(void)size;
}

size_t	count_blocks(const t_list *head)
{
	size_t	blocks;

	blocks = 0;
	while (head)
	{
		blocks += ((t_file *)head->content)->stat.st_blocks; //TODO: support blocksize other than 512 ?
		head = head->next;
	}
	return (blocks);
}
