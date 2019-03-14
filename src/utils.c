#include "ft_ls.h"

t_file	*f(t_list *node)
{
	return ((t_file *)node->content);
}

void		del_node(void *file, size_t size)
{
	free((t_file *)file);
	file = NULL;
	(void)size;
}
#include <stdio.h>
size_t		count_blocks(const t_list *head)
{
	size_t			blocks;
	char			*path;

	blocks = 0;
	path = ((t_file *)head->content)->path;
	while (head)
	{ //TODO: support blocksize other than 512 ?
		blocks += ((t_file *)head->content)->stat.st_blocks;
		//printf("blocks : %zu, st_blocks : %lld, size: %lld, nom: %s\n", blocks, ((t_file *)head->content)->stat.st_blocks, ((t_file *)head->content)->stat.st_size, ((t_file *)head->content)->name);
		if (ft_strcmp(path, ((t_file *)head->content)->path) != 0)
 			return (blocks);
		head = head->next;
	}
	return (blocks);
}

size_t		*tab_to_max(size_t *tab, t_list *node)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(f(node)->stat.st_uid);
	gr = getgrgid(f(node)->stat.st_gid);
	if (pw == 0 || gr == 0)  //TODO: protect
		return (NULL);	//TODO: tab[0] pour les perms
	if (ft_strlen(ft_itoa(f(node)->stat.st_nlink)) > tab[1])
		tab[1] = ft_strlen(ft_itoa((f(node)->stat.st_nlink)));
	if (ft_strlen(pw->pw_name) > tab[2])
		tab[2] = ft_strlen(pw->pw_name);
	if (ft_strlen(gr->gr_name) > tab[3])
		tab[3] = ft_strlen(gr->gr_name);
	if (S_ISCHR(f(node)->stat.st_mode)
			|| S_ISBLK(f(node)->stat.st_mode))
	{
		if (ft_strlen(ft_itoa(major(f(node)->stat.st_rdev))) > tab[4])
			tab[4] = ft_strlen(ft_itoa(major(f(node)->stat.st_rdev)));
		if (ft_strlen(ft_itoa(minor(f(node)->stat.st_rdev))) > tab[5])
			tab[5] = ft_strlen(ft_itoa(minor(f(node)->stat.st_rdev)));
	}
	else if (ft_strlen(ft_itoa(f(node)->stat.st_size)) > tab[4])
		tab[4] = ft_strlen(ft_itoa(f(node)->stat.st_size));
	return (tab);
}

size_t		*len_max(t_list *node)
{
	size_t			*tab;
	char			*dirpath;
	ssize_t			xattr;

	if (!(tab = ft_sizet_tab(7)))
		return (NULL);
	dirpath = ft_strjoin(f(node)->path
			, f(node)->name); //TODO: leaks
	dirpath = ft_strjoin(dirpath, "/");
	while (node)
	{
		if (!ft_strcmp(dirpath, f(node)->path))
		{
			tab_to_max(tab, node);
#ifndef __APPLE__
			if (!tab[6])
			{
				xattr = listxattr(ft_strjoin(f(node)->path
							, f(node)->name), NULL, 0); //TODO: protect + leaks
				if (xattr >= 1)
					tab[6] = 1;
			}
#endif
			(void)xattr;
		}
		node = node->next;
	}
	return (tab);
}
