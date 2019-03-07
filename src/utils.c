#include "ft_ls.h"

int		lstcmp(const t_list *node1, const t_list *node2)
{
	char		*fullpath1;
	char		*fullpath2;

	//TODO: handle -r
	if (g_flags.t)
		return (((t_file *)node1->content)->stat.ST_MTIME
				> ((t_file *)node2->content)->stat.ST_MTIME);
	else
	{
		fullpath1 = ft_strjoin(((t_file *)node1->content)->path
					, ((t_file *)node1->content)->name);
		fullpath2 = ft_strjoin(((t_file *)node2->content)->path
					, ((t_file *)node2->content)->name);
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
		//TODO: support blocksize other than 512 ?
		blocks += ((t_file *)head->content)->stat.st_blocks;
		head = head->next;
	}
	return (blocks);
}

size_t	*len_max(t_list *node)
{
	size_t			*tab;
	char			*dirpath;
	ssize_t			xattr;
	struct passwd	*pw;
	struct group	*gr;

	if(!(tab = malloc(sizeof(size_t) * 7)))
		return (NULL);
	//ft_memset(tab, 0, 6);
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
	tab[6] = 0;
	dirpath = ft_strjoin(((t_file *)node->content)->path
			, ((t_file *)node->content)->name); //TODO: leaks
	dirpath = ft_strjoin(dirpath, "/");

	while (node)
	{
		if (!ft_strcmp(dirpath, ((t_file *)node->content)->path))
		{

			pw = getpwuid(((t_file *)node->content)->stat.st_uid);
			gr = getgrgid(((t_file *)node->content)->stat.st_gid);
			if (pw == 0 || gr == 0)
				return (NULL); //TODO: protect
			//TODO: tab[0] pour les perms
			if (ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_nlink))
					> tab[1])
				tab[1] = ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_nlink));
			if (ft_strlen(pw->pw_name) > tab[2])
				tab[2] = ft_strlen(pw->pw_name);
			if (ft_strlen(gr->gr_name) > tab[3])
				tab[3] = ft_strlen(gr->gr_name);
			if (S_ISCHR(((t_file *)node->content)->stat.st_mode)
					|| S_ISBLK(((t_file *)node->content)->stat.st_mode))
			{
				if (ft_strlen(ft_itoa(major(((t_file *)node->content)->stat.st_rdev))) > tab[4])
					tab[4] = ft_strlen(ft_itoa(major(((t_file *)node->content)->stat.st_rdev)));
				if (ft_strlen(ft_itoa(minor(((t_file *)node->content)->stat.st_rdev))) > tab[5])
					tab[5] = ft_strlen(ft_itoa(minor(((t_file *)node->content)->stat.st_rdev)));
			}
			else if (ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_size)) > tab[4])
				tab[4] = ft_strlen(ft_itoa(((t_file *)node->content)->stat.st_size));
			if (!tab[6])
			{
				xattr = listxattr(ft_strjoin(((t_file *)node->content)->path
							, ((t_file *)node->content)->name), NULL, 0
						, XATTR_NOFOLLOW); //TODO: protect + leaks
				if (xattr >= 1)
					tab[6] = 1;
			}
		}
		node = node->next;
	}
	return (tab);
}
