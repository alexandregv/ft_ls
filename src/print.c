/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:26 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/17 17:23:58 by aguiot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		color_modes(t_file *file)
{
	if (S_ISDIR(file->stat.st_mode))
		if (file->stat.st_mode == 17407)
			ft_putstr(COLOR_DIRT);
		else
			ft_putstr(COLOR_DIR);
	else if (S_ISLNK(file->stat.st_mode))
		ft_putstr(COLOR_LNK);
	else if (S_ISFIFO(file->stat.st_mode))
		ft_putstr(COLOR_FIFO);
	else if (S_ISSOCK(file->stat.st_mode))
		ft_putstr(COLOR_SOCK);
	else if (S_ISBLK(file->stat.st_mode))
		ft_putstr(COLOR_BLK);
	else if (S_ISCHR(file->stat.st_mode))
		ft_putstr(COLOR_CHR);
	else if (S_ISREG(file->stat.st_mode) && file->stat.st_mode & S_IXUSR)
	{
		if (file->stat.st_mode == 36349)
			ft_putstr(COLOR_REGS);
		else
			ft_putstr(COLOR_EXEC);
	}
}

void			print_filename(t_file *file)
{
	char	buf[PATH_MAX + NAME_MAX];

	if (g_flags.g_up)
		color_modes(file);
	ft_putstr(file->name);
	if (g_flags.g_up)
		ft_putstr(COLOR_RESET);
	if (S_ISLNK(file->stat.st_mode))
	{
		ft_putstr(" -> ");
		write(1, buf, readlink(file->full_path, buf
					, PATH_MAX + NAME_MAX)); //TODO: protect + leak
	}
	ft_putchar('\n');
}

static void		print_summary(t_list *list, size_t *tab)
{
	char	*dirpath;

	dirpath = ft_strjoin(f(list)->full_path, "/");
	while (list)
	{
		if (!ft_strcmp(dirpath, f(list)->path))
			print_file(list, tab);
		list = list->next;
	}
	free(dirpath);
}

static void		print_dirs(t_list *list, int files_count)
{
	list = list->next;
	while (list)
	{
		if (S_ISDIR(f(list)->stat.st_mode))
			if (print_all(list, files_count))
				return ;
		list = list->next;
	}
}

int				print_all(t_list *list, int files_count)
{
	t_list	*ptr;
	size_t	*tab;

	ptr = list;
	tab = g_flags.l ? len_max(list) : NULL; //TODO: add protect ?
	if (ft_strcmp(f(list)->name, ".") != 0
			&& ft_strcmp(f(list)->name, "..") != 0)
	{
		if (*f(list)->name)
			ft_putchar('\n');
		if (g_flags.r_up || files_count > 1)
		{
			ft_putstr(f(list)->full_path);
			ft_putendl(":");
		}
		if (g_flags.l)
		{
			ft_putstr("total ");
			ft_putnbr(count_blocks(list->next));
			ft_putchar('\n');
		}
	}
	print_summary(list, tab);
	if (g_flags.r_up)
		print_dirs(list, files_count);
	free(tab);
	if (list == ptr)
		return (1);
	return (0);
}
