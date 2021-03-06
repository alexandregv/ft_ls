/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:17:55 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 01:54:41 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file
	*f(t_list *node)
{
	return ((t_file *)node->content);
}

size_t
	count_blocks(t_list *head)
{
	size_t			blocks;
	char			*path;
	size_t			slashes;
	size_t			curr_slashes;
	size_t			i;

	blocks = 0;
	path = f(head)->path;

	i = 0;
	slashes = 0;
	while (f(head)->path[i])
		if (f(head)->path[i++] == '/')
			++slashes;

	while (head)
	{
		//printf("blocks : %zu, st_blocks : %lld, size: %lld, nom: %s\n"
		//		, blocks, ((t_file *)head->content)->stat.st_blocks
		//		, ((t_file *)head->content)->stat.st_size
		//		, ((t_file *)head->content)->name);
		if (!ft_strcmp(path, f(head)->path))
			blocks += f(head)->stat.st_blocks;

		i = 0;
		curr_slashes = 0;
		while (f(head)->path[i])
			if (f(head)->path[i++] == '/')
				++curr_slashes;
		if (curr_slashes < slashes)
			break ;
		head = head->next;
	}
	return (blocks);
}

static void
	an_if_forest(size_t *tab, t_list *node, struct passwd *pw, struct group *gr)
{
	char			*itoa;

	if (ft_strlen(itoa = ft_itoa(f(node)->stat.st_nlink)) > tab[1])
		tab[1] = ft_strlen(itoa);
	free(itoa);
	if (ft_strlen(pw->pw_name) > tab[2])
		tab[2] = ft_strlen(pw->pw_name);
	if (ft_strlen(gr->gr_name) > tab[3])
		tab[3] = ft_strlen(gr->gr_name);
	if (S_ISCHR(f(node)->stat.st_mode)
			|| S_ISBLK(f(node)->stat.st_mode))
	{
		if (ft_strlen(itoa = ft_itoa(major(f(node)->stat.st_rdev))) > tab[4])
			tab[4] = ft_strlen(itoa);
		if (itoa)
			free(itoa);
		itoa = NULL;
		if (ft_strlen(itoa = ft_itoa(minor(f(node)->stat.st_rdev))) > tab[5])
			tab[5] = ft_strlen(itoa);
	}
	else if (ft_strlen(itoa = ft_itoa(f(node)->stat.st_size)) > tab[4])
		tab[4] = ft_strlen(itoa);
	if (itoa)
		free(itoa);
}

size_t
	*tab_to_max(size_t *tab, t_list *node)
{
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(f(node)->stat.st_uid);
	gr = getgrgid(f(node)->stat.st_gid);
	if (pw == 0 || gr == 0)
		return (NULL);
	an_if_forest(tab, node, pw, gr);
	return (tab);
}

size_t
	*len_max(t_list *node)
{
	size_t			*tab;
	char			*dirpath;
	ssize_t			xattr;
	size_t			slashes;
	size_t			curr_slashes;
	size_t			i;

	if (!(tab = ft_sizet_tab(7)))
		return (NULL);
	dirpath = ft_strjoin(f(node)->full_path, "/");

	i = 0;
	slashes = 0;
	while (f(node)->path[i])
		if (f(node)->path[i++] == '/')
			++slashes;

	while (node)
	{
		if (!ft_strcmp(dirpath, f(node)->path))
		{
			tab_to_max(tab, node);
#ifndef __APPLE__
			if (!tab[6])
			{
				xattr = listxattr(f(node)->full_path, NULL, 0);
				if (xattr >= 1)
					tab[6] = 1;
			}
#endif
			(void)xattr;
		}
		i = 0;
		curr_slashes = 0;
		while (f(node)->path[i])
			if (f(node)->path[i++] == '/')
				++curr_slashes;
		if (curr_slashes < slashes)
			break ;
		node = node->next;
	}
	free(dirpath);
	return (tab);
}
