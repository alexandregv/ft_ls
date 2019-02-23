/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:08:10 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/23 13:08:12 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	DIR				*dirp;
	struct dirent	*direntp;

	if (ac != 2)
		ft_die("Usage: ./ft_list_dir directory_name", 0);
	dirp = opendir(av[1]);
	if (dirp == NULL)
		ft_die("Error openening directory.", 1);
	while ((direntp = readdir(dirp)))
	{
		ft_putstr(direntp->d_name);
		ft_putchar('\n');
	}
	closedir(dirp);
	return (0);
}
