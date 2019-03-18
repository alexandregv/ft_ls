/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:25:20 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 18:37:59 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*norm_lol(t_list *files, t_list *dirs)
{
	if (!g_flags.f)
	{
		if (files != NULL)
			ft_list_sort(&files, (int (*)(const void*, const void*))ft_strcmp);
		if (dirs != NULL)
			ft_list_sort(&dirs, (int (*)(const void*, const void*))ft_strcmp);
	}
	if (!g_flags.f && g_flags.r)
	{
		if (files != NULL)
			ft_list_rev(&files);
		if (dirs != NULL)
			ft_list_rev(&dirs);
	}
	if (files != NULL)
	{
		ft_list_last(files)->next = dirs;
		return (files);
	}
	else
		return (dirs);
}

t_list			*sort_args(char **fv)
{
	t_list	*files;
	t_list	*dirs;
	t_stat	statb;
	t_list	*new;
	size_t	i;

	files = NULL;
	dirs = NULL;
	i = 0;
	while (fv[i++])
		if (stat(fv[i - 1], &statb) != -1)
		{
			new = ft_list_new(ft_strdup(fv[i - 1]), statb.st_mode, 0);
			ft_list_push_back(S_ISDIR(statb.st_mode) ? &dirs : &files, new);
		}
		else
		{
			ft_putstr("ft_ls: '");
			ft_putstr(fv[i - 1]);
			ft_putendl("': No such file or directory");
		}
	return (norm_lol(files, dirs));
}
