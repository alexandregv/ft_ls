/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:19:26 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 19:40:06 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		color_modes(t_file *file, char **ptr)
{
	if (S_ISDIR(file->stat.st_mode))
		if (file->stat.st_mode == 17407)
			add_to_buff(ptr, COLOR_DIRT, ft_strlen(COLOR_DIRT), 0);
		else
			add_to_buff(ptr, COLOR_DIR, ft_strlen(COLOR_DIR), 0);
	else if (S_ISLNK(file->stat.st_mode))
		add_to_buff(ptr, COLOR_LNK, ft_strlen(COLOR_LNK), 0);
	else if (S_ISFIFO(file->stat.st_mode))
		add_to_buff(ptr, COLOR_FIFO, ft_strlen(COLOR_FIFO), 0);
	else if (S_ISSOCK(file->stat.st_mode))
		add_to_buff(ptr, COLOR_SOCK, ft_strlen(COLOR_SOCK), 0);
	else if (S_ISBLK(file->stat.st_mode))
		add_to_buff(ptr, COLOR_BLK, ft_strlen(COLOR_BLK), 0);
	else if (S_ISCHR(file->stat.st_mode))
		add_to_buff(ptr, COLOR_CHR, ft_strlen(COLOR_CHR), 0);
	else if (S_ISREG(file->stat.st_mode) && file->stat.st_mode & S_IXUSR)
	{
		if (file->stat.st_mode == 36349)
			add_to_buff(ptr, COLOR_REGS, ft_strlen(COLOR_REGS), 0);
		else
			add_to_buff(ptr, COLOR_EXEC, ft_strlen(COLOR_EXEC), 0);
	}
}

void			print_filename(t_file *file, char **ptr)
{
	char	buff[PATH_MAX + NAME_MAX];

	if (g_flags.g_up)
		color_modes(file, ptr);
	add_to_buff(ptr, file->name, ft_strlen(file->name), 0);
	if (g_flags.g_up)
		add_to_buff(ptr, COLOR_RESET, ft_strlen(COLOR_RESET), 0);
	if (S_ISLNK(file->stat.st_mode))
	{
		if (g_flags.f_up)
			*(*ptr)++ = '@';
		add_to_buff(ptr, " -> ", 4, 0);
		add_to_buff(ptr, buff, readlink(file->full_path, buff
					, PATH_MAX + NAME_MAX), 1);
	}
	if (g_flags.f_up && S_ISDIR(file->stat.st_mode))
		*(*ptr)++ = '/';
	else if (g_flags.f_up && S_ISREG(file->stat.st_mode)
			&& file->stat.st_mode & S_IXUSR)
		*(*ptr)++ = '*';
	else if (g_flags.f_up && S_ISSOCK(file->stat.st_mode))
		*(*ptr)++ = '=';
	else if (g_flags.f_up && S_ISFIFO(file->stat.st_mode))
		*(*ptr)++ = '|';
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
	t_list	*backup;
	size_t	*tab;
	char	*buff;
	char	*ptr;

	buff = ft_strnew(PATH_MAX + NAME_MAX + 255);
	ptr = buff;
	backup = list;
	tab = g_flags.l ? len_max(list) : NULL;
	if_notcurr(list, files_count, ptr, buff);
	print_summary(list, tab);
	if (g_flags.r_up)
		print_dirs(list, files_count);
	free(tab);
	free(buff);
	if (list == backup)
		return (1);
	return (0);
}
