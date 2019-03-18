/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboulaao <sboulaao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:24:38 by sboulaao          #+#    #+#             */
/*   Updated: 2019/03/18 15:03:03 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	if_notcurr(t_list *list, int files_count, char *ptr, char *buff)
{
	char	*itoa;

	if (ft_strcmp(f(list)->name, ".") != 0
			&& ft_strcmp(f(list)->name, "..") != 0)
	{
		if (*f(list)->name)
			add_to_buff(&ptr, "\n", 1, 0);
		if (g_flags.r_up || files_count > 1)
		{
			add_to_buff(&ptr, f(list)->full_path
					, ft_strlen(f(list)->full_path), 0);
			add_to_buff(&ptr, ":\n", 2, 0);
		}
		if (g_flags.l)
		{
			add_to_buff(&ptr, "total ", 6, 0);
			itoa = ft_itoa(count_blocks(list->next));
			add_to_buff(&ptr, itoa, ft_strlen(itoa), 0);
			add_to_buff(&ptr, "\n", 1, 0);
			free(itoa);
		}
		ft_putstr(buff);
	}
}

void	while_slashes(t_list *head, char *path, size_t slashes, size_t blocks)
{
	int				i;
	size_t			curr_slashes;

	while (head)
	{
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
}

void	while_node(t_list *node, char *dirpath, size_t *tab, size_t slashes)
{
	int				i;
	size_t			curr_slashes;

	while (node)
	{
		if (!ft_strcmp(dirpath, f(node)->path))
			tab_to_max(tab, node);
		i = 0;
		curr_slashes = 0;
		while (f(node)->path[i])
			if (f(node)->path[i++] == '/')
				++curr_slashes;
		if (curr_slashes < slashes)
			break ;
		node = node->next;
	}
}