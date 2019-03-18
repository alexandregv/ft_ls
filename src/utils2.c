/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:17:50 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 13:54:18 by sboulaao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		lstcmp(t_list *node1, t_list *node2)
{
	if (g_flags.t)
	{
		if (g_flags.r)
			return (f(node1)->stat.ST_MTIME < f(node2)->stat.ST_MTIME);
		if (f(node1)->stat.ST_MTIME == f(node2)->stat.ST_MTIME)
			return (ft_strcmp(f(node1)->full_path, f(node2)->full_path) < 0);
		return (f(node1)->stat.ST_MTIME > f(node2)->stat.ST_MTIME);
	}
	else
		return (ft_strcmp(f(node1)->full_path, f(node2)->full_path) < 0);
}

void	manual_add(t_list **list, t_list *args, int mode)
{
	t_file *new;

	if (mode == 1)
	{
		new = (t_file *)malloc(sizeof(t_file));
		ft_list_push_back(list, ft_list_new(new, sizeof(t_file), 0));
		ft_strcpy(new->path, (char *)args->content);
		ft_strcpy(new->name, "");
		ft_strcpy(new->full_path, (char *)args->content);
		ft_strcat(new->full_path, "");
	}
	else if (mode == 2)
	{
		new = (t_file *)malloc(sizeof(t_file));
		ft_list_push_front(list, ft_list_new(new, sizeof(t_file), 0));
		ft_strcpy(new->path, (char *)args->content);
		ft_strcpy(new->name, "");
		ft_strcpy(new->full_path, (char *)args->content);
	}
}

void	add_first_file(t_list **list, t_list *args)
{
	t_file	*first;

	first = (t_file *)malloc(sizeof(t_file));
	ft_strcpy(first->path, (char *)args->content);
	ft_strcpy(first->name, "");
	ft_strcpy(first->full_path, (char *)args->content);
	ft_strcat(first->full_path, "");
	ft_list_push_front(list, ft_list_new(first, sizeof(t_file), 0));
}

void	add_to_buff(char **ptr, char *str, size_t size, int trunc)
{
	**ptr = '\0';
	if (trunc)
		ft_strncat(*ptr, str, size);
	else
		ft_strcat(*ptr, str);
	*ptr += size;
}
