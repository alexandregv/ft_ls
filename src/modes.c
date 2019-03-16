/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:17:27 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 21:22:23 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_fileowner(t_stat statb, size_t max)
{
	struct passwd	*pw;

	pw = getpwuid(statb.st_uid);
	if (pw != 0)
	{
		ft_putstr(pw->pw_name);
		align(pw->pw_name, max);
	}
}

void		print_filegroup(t_stat statb, size_t max)
{
	struct group	*gr;

	gr = getgrgid(statb.st_gid);
	if (gr != 0)
	{
		ft_putstr(gr->gr_name);
		align(gr->gr_name, max);
	}
}

char		*get_filemodes(char *modes, mode_t mode, char *fullpath)
{
	modes[10] = ' ';
	modes[11] = '\0';
	modes[1] = mode & S_IRUSR ? 'r' : '-';
	modes[2] = mode & S_IWUSR ? 'w' : '-';
	modes[3] = mode & S_IXUSR ? 'x' : '-';
	modes[3] = mode & S_ISUID ? 's' : modes[3];
	modes[4] = mode & S_IRGRP ? 'r' : '-';
	modes[5] = mode & S_IWGRP ? 'w' : '-';
	modes[6] = mode & S_IXGRP ? 'x' : '-';
	modes[6] = mode & S_ISGID ? 's' : modes[6];
	modes[7] = mode & S_IROTH ? 'r' : '-';
	modes[8] = mode & S_IWOTH ? 'w' : '-';
	if ((mode & S_IXOTH) && !(mode & S_ISVTX))
		modes[9] = 'x';
	else if (!(mode & S_IXOTH) && (mode & S_ISVTX))
		modes[9] = 'T';
	else if ((mode & S_IXOTH) && (mode & S_ISVTX))
		modes[9] = 't';
#ifdef __APPLE__
	if (acl_get_file(fullpath, ACL_TYPE_EXTENDED))
		modes[10] = '+';
	if (listxattr(fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
		modes[10] = '@';
#else
	if (listxattr(fullpath, NULL, 0) > 0)
		modes[10] = '+';
#endif
	return (modes);
}

void		print_filemodes(t_list *node)
{
	mode_t			mode;
	char			modes[12];
	char			*fullpath;

	if (!ft_strncmp(f(node)->path, f(node)->name, ft_strlen(f(node)->path) - 1))
		fullpath = f(node)->name;
	else
		fullpath = f(node)->full_path;
	mode = f(node)->stat.st_mode;
	ft_memset(modes, '-', 10);
	if (S_ISDIR(mode))
		modes[0] = 'd';
	else if (S_ISCHR(mode))
		modes[0] = 'c';
	else if (S_ISBLK(mode))
		modes[0] = 'b';
	else if (S_ISLNK(mode))
		modes[0] = 'l';
	else if (S_ISSOCK(mode))
		modes[0] = 's';
	else if (S_ISFIFO(mode))
		modes[0] = 'p';
	get_filemodes(modes, mode, fullpath);
	ft_putstr(modes);
}
