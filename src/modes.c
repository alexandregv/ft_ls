/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulaao <sboulaao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:53:30 by sboulaao          #+#    #+#             */
/*   Updated: 2019/03/18 20:17:30 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_fileowner(t_stat statb, size_t max, char **ptr)
{
	struct passwd	*pw;

	if (g_flags.g)
		return ;
	pw = getpwuid(statb.st_uid);
	if (pw != 0)
	{
		add_to_buff(ptr, pw->pw_name, ft_strlen(pw->pw_name), 0);
		align(pw->pw_name, max, ptr);
	}
}

void		print_filegroup(t_stat statb, size_t max, char **ptr)
{
	struct group	*gr;

	gr = getgrgid(statb.st_gid);
	if (gr != 0)
	{
		add_to_buff(ptr, gr->gr_name, ft_strlen(gr->gr_name), 0);
		align(gr->gr_name, max, ptr);
	}
	*(*ptr)++ = ' ';
}

static void	set_filemodes(char **modes, mode_t mode, char *fullpath)
{
	(*modes)[10] = ' ';
	(*modes)[1] = mode & S_IRUSR ? 'r' : '-';
	(*modes)[2] = mode & S_IWUSR ? 'w' : '-';
	(*modes)[3] = mode & S_IXUSR ? 'x' : '-';
	(*modes)[3] = mode & S_ISUID ? 's' : (*modes)[3];
	(*modes)[4] = mode & S_IRGRP ? 'r' : '-';
	(*modes)[5] = mode & S_IWGRP ? 'w' : '-';
	(*modes)[6] = mode & S_IXGRP ? 'x' : '-';
	(*modes)[6] = mode & S_ISGID ? 's' : (*modes)[6];
	(*modes)[7] = mode & S_IROTH ? 'r' : '-';
	(*modes)[8] = mode & S_IWOTH ? 'w' : '-';
	if ((mode & S_IXOTH) && !(mode & S_ISVTX))
		(*modes)[9] = 'x';
	else if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		(*modes)[9] = 'T';
	else if ((mode & S_IXOTH) && (mode & S_ISVTX))
		(*modes)[9] = 't';
	if (acl_get_file(fullpath, ACL_TYPE_EXTENDED))
		(*modes)[10] = '+';
	if (listxattr(fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
		(*modes)[10] = '@';
	*modes += 10;
}

void		print_filemodes(t_list *node, char **modes)
{
	mode_t			mode;
	char			*fullpath;

	if (!ft_strncmp(f(node)->path, f(node)->name, ft_strlen(f(node)->path) - 1))
		fullpath = f(node)->name;
	else
		fullpath = f(node)->full_path;
	mode = f(node)->stat.st_mode;
	ft_memset(*modes, '-', 10);
	(*modes)[11] = '\0';
	if (S_ISDIR(mode))
		(*modes)[0] = 'd';
	else if (S_ISCHR(mode))
		(*modes)[0] = 'c';
	else if (S_ISBLK(mode))
		(*modes)[0] = 'b';
	else if (S_ISLNK(mode))
		(*modes)[0] = 'l';
	else if (S_ISSOCK(mode))
		(*modes)[0] = 's';
	else if (S_ISFIFO(mode))
		(*modes)[0] = 'p';
	set_filemodes(modes, mode, fullpath);
}
