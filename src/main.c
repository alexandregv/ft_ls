/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:17:43 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:19:40 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "ft_ls.h"

static void		lol(t_file **new, t_list **list, t_dirent *direntp, char *path)
{
	if ((g_flags.a) || direntp->d_name[0] != '.'
			|| ((g_flags.a_up && ft_strcmp(direntp->d_name, ".")) != 0
				&& (g_flags.a_up && ft_strcmp(direntp->d_name, "..") != 0)))
	{
		*new = (t_file *)malloc(sizeof(t_file));
		ft_strcpy((*new)->name, direntp->d_name);
		ft_strcat(ft_strcpy((*new)->path, path), "/");
		ft_strcat(ft_strcpy((*new)->full_path, (*new)->path), (*new)->name);
		lstat((*new)->full_path, &(*new)->stat); //TODO: add protect
		if (g_flags.r_up && direntp->d_type == DT_DIR
				&& ft_strcmp(direntp->d_name, ".") != 0
				&& ft_strcmp(direntp->d_name, "..") != 0)
			*list = ft_while(*list, (*new)->full_path);
		ft_list_push_back(list, ft_list_new(*new, sizeof(**new), 0));
	}
}

t_list			*ft_while(t_list *list, char *path)
{
	DIR			*dirp;
	t_dirent	*direntp;
	t_file		*new;
	t_stat		statb;

	stat(path, &statb); //TODO: add protect
	if (!S_ISDIR(statb.st_mode))
	{
		new = (t_file *)malloc(sizeof(t_file));
		ft_strcpy(new->name, path);
		ft_strcat(ft_strcpy(new->path, path), "/");
		lstat(path, &new->stat); //TODO: add protect
		ft_list_push_back(&list, ft_list_new(new, sizeof(t_file), 0));
		return (list);
	}
	dirp = opendir(path);
	if (dirp == NULL)
	{
		perror("ft_ls");
		return (list);
	}
	while ((direntp = readdir(dirp)))
		lol(&new, &list, direntp, path);
	closedir(dirp);
	return (list);
}

static void		ls_each(int fc, int *i, t_list **list, t_list *args)
{
	if ((fc >= 2 || (g_flags.r_up)) && S_ISDIR(args->content_size) && i)
		ft_putchar('\n');
	DEBUGstr("Starting path = ");
	DEBUGendl(args->content);
	*list = ft_while(*list, args->content);
	if (list)
	{
		DEBUGendl("------------List before sort----------------");
		DEBUG(ft_list_iter(*list, print_dir, 0));
		if (!g_flags.u_up)
		{
			*list = ft_dlist_msort(*list, lstcmp);
			if (g_flags.r)
				ft_dlist_rev(list);
			DEBUGendl("------------List after sort----------------");
			DEBUG(ft_list_iter(*list, print_dir, 0));
		}
		handle_r(list, args);
		add_first_file(list, args);
		DEBUGendl("------------Print all----------------");
		print_all(*list, fc);
		++*i;
		ft_list_del(list, NULL);
	}
	args = args->next;
}

int				main(int ac, char **av)
{
	t_list		*args;
	t_list		*list;
	char		**fv;
	int			nums[3];

	nums[0] = parse_flags(ac, av);
	if (nums[0] == -1)
		return (0);
	DEBUG(debug_flags(nums[0]));
	list = NULL;
	nums[1] = ac - nums[0];
	fv = av + nums[0];
	if (nums[1] == 0)
	{
		nums[1] = 1;
		fv = (char *[]) {".", NULL};
	}
	args = sort_args(fv);
	nums[2] = 0;
	while (nums[2] < nums[1] && args)
		ls_each(nums[1], &nums[2], &list, args);
	ft_list_del(&args, NULL);
	return (EXIT_SUCCESS);
}
