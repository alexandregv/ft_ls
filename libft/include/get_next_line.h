/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:54:37 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/16 10:23:33 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 130

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef	struct s_gnl_file	t_gnl_file;
struct			s_gnl_file
{
	char		*remainder;
	char		*tmp;
	size_t		fd;
	t_gnl_file	*next;
};

int				get_next_line(const int fd, char **line);

#endif
