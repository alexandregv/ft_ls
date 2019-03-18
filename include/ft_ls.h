/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:16:50 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 16:04:07 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <dirent.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/acl.h>
# include "libft.h"
# include "struct.h"

# define COLOR_RESET       "\033[0m"
# define COLOR_BOLD_BLUE   "\033[1;94m"
# define COLOR_CYAN        "\033[1;36m"
# define COLOR_YELLOW      "\033[33m"
# define COLOR_MAGENTA     "\033[35m"
# define COLOR_BOLD_YELLOW "\033[1;33m"
# define COLOR_BOLD_GREEN  "\033[1;32m"
# define COLOR_BG_GREEN    "\033[30;42m"
# define COLOR_RED         "\033[31m"
# define COLOR_BG_RED      "\033[30;41m"

# define COLOR_DIR  COLOR_CYAN
# define COLOR_DIRT COLOR_BG_GREEN
# define COLOR_LNK  COLOR_MAGENTA
# define COLOR_FIFO COLOR_YELLOW
# define COLOR_SOCK COLOR_MAGENTA
# define COLOR_BLK  COLOR_BOLD_YELLOW
# define COLOR_CHR  COLOR_BOLD_YELLOW
# define COLOR_EXEC COLOR_RED
# define COLOR_OLNK COLOR_BOLD_GREEN
# define COLOR_REGS COLOR_BG_RED

# define ST_MTIME st_mtimespec.tv_sec
# define FT_XATTR_NOFOLLOW 0, XATTR_NOFOLLOW
# define OWNER_GROUP_SEPARATOR "  "
# define SIZE_SEPARATOR 1

typedef struct timespec	t_timespec;
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct	s_file
{
	char		name[NAME_MAX + 1];
	char		path[PATH_MAX];
	char		full_path[NAME_MAX + PATH_MAX];
	t_stat		stat;
}				t_file;

int				parse_flags(int ac, char **av);
t_list			*sort_args(char **fv);
int				lstcmp(t_list *node1, t_list *node2);
size_t			count_blocks(t_list *head);
int				print_all(t_list *list, int files_count);
void			print_file(t_list *node, size_t *tab);
void			print_filename(t_file *file, char **ptr);
size_t			*len_max(t_list *node);
t_file			*f(t_list *node);
void			print_fileowner(t_stat statb, size_t max, char **ptr);
void			print_filegroup(t_stat statb, size_t max, char **ptr);
void			print_filemodes(t_list *node, char **ptr);
void			align(char *str, size_t max, char **ptr);
void			print_dir(t_list *node);
void			manual_add(t_list **list, t_list *args, int mode);
void			add_first_file(t_list **list, t_list *args);
t_list			*fix_reverse_dirs(t_list *head);
void			handle_r(t_list **list, t_list *args);
t_list			*ft_while(t_list *list, char *path);
void			add_to_buff(char **ptr, char *str, size_t inc, int trunc);
void			while_slashes(t_list *head, char *path, size_t slashes
				, size_t *blocks);
void			while_node(t_list *node, char *dirpath, size_t *tab
				, size_t slashes);
size_t			*tab_to_max(size_t *tab, t_list *node);
void			if_notcurr(t_list *list, int files_count, char *ptr
				, char *buff);

#endif
