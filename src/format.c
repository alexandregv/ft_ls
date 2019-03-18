/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulaao <sboulaao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:55:06 by sboulaao          #+#    #+#             */
/*   Updated: 2019/03/18 21:00:24 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_time(t_stat statb, char **ptr)
{
	char	*temps;
	time_t	now;

	temps = ctime(&statb.ST_MTIME);
	time(&now);
	if ((now - statb.ST_MTIME) >= 15552000)
	{
		add_to_buff(ptr, temps += 4, 7, 1);
		add_to_buff(ptr, " ", 1, 1);
		add_to_buff(ptr, temps += 16, 4, 1);
	}
	else
		add_to_buff(ptr, temps += 4, 12, 1);
	*(*ptr)++ = ' ';
}

static void	print_size(t_stat statb, size_t *max, char **ptr)
{
	char	*size;

	if (S_ISCHR(statb.st_mode) || S_ISBLK(statb.st_mode))
	{
		size = ft_itoa(major(statb.st_rdev));
		align(size, max[0], ptr);
		add_to_buff(ptr, size, ft_strlen(size), 0);
		free(size);
		add_to_buff(ptr, ", ", 2, 0);
		size = ft_itoa(minor(statb.st_rdev));
		align(size, max[1], ptr);
		add_to_buff(ptr, size, ft_strlen(size), 0);
		free(size);
	}
	else
	{
		size = ft_itoa(statb.st_size);
		align(size, max[0] + max[1] + (max[1] == 0 ? SIZE_SEPARATOR : 1), ptr);
		add_to_buff(ptr, size, ft_strlen(size), 0);
		free(size);
	}
	*(*ptr)++ = ' ';
}

static void	print_inode(t_list *node, char **ptr)
{
	char	*inode;

	if (!g_flags.i)
		return ;
	inode = ft_itoa(f(node)->stat.st_ino);
	add_to_buff(ptr, inode, ft_strlen(inode), 0);
	free(inode);
	*(*ptr)++ = ' ';
}

static void	l_flag(t_list *node, char **ptr, size_t *tab)
{
	char	*links;

	print_filemodes(node, ptr);
	*(*ptr)++ = ' ';
	links = ft_itoa(f(node)->stat.st_nlink);
	align(links, tab[1], ptr);
	add_to_buff(ptr, links, ft_strlen(links), 0);
	*(*ptr)++ = ' ';
	print_fileowner(f(node)->stat, tab[2], ptr);
	if (!g_flags.g)
		add_to_buff(ptr, OWNER_GROUP_SEPARATOR
				, ft_strlen(OWNER_GROUP_SEPARATOR), 0);
	print_filegroup(f(node)->stat, tab[3], ptr);
	print_size(f(node)->stat, tab + 4, ptr);
	print_time(f(node)->stat, ptr);
	free(links);
}

void		print_file(t_list *node, size_t *tab)
{
	char	buff[PATH_MAX + NAME_MAX + 255];
	char	*ptr;

	ptr = buff;
	ft_memset(buff, ' ', PATH_MAX + NAME_MAX + 255);
	print_inode(node, &ptr);
	if (g_flags.l)
		l_flag(node, &ptr, tab);
	print_filename(f(node), &ptr);
	if (g_flags.m && node->next)
	{
		*ptr++ = ',';
		*ptr++ = ' ';
	}
	else
		*ptr++ = '\n';
	*ptr++ = '\0';
	ft_putstr(buff);
}
