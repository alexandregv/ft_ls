#ifndef FT_LS_H
# define FT_LS_H

# ifndef __APPLE__
#  include <sys/sysmacros.h>
# endif
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

# include "debug.h"

# define COLOR_RESET       "\e[0m"
# define COLOR_BOLD_BLUE   "\e[1;94m"
# define COLOR_CYAN        "\e[1;36m"
# define COLOR_YELLOW      "\e[33m"
# define COLOR_MAGENTA     "\e[35m"
# define COLOR_BOLD_YELLOW "\e[1;33m"
# define COLOR_BOLD_GREEN  "\e[1;32m"
# define COLOR_RED         "\e[31m"

# ifndef __APPLE__
# define COLOR_DIR  COLOR_CYAN
# define COLOR_LNK  COLOR_BOLD_BLUE
# define COLOR_FIFO COLOR_YELLOW
# define COLOR_SOCK COLOR_MAGENTA
# define COLOR_BLK  COLOR_BOLD_YELLOW
# define COLOR_CHR  COLOR_BOLD_YELLOW
# define COLOR_EXEC COLOR_RED
# define COLOR_OLNK COLOR_BOLD_GREEN
# endif

# define COLOR_DIR  COLOR_CYAN
# define COLOR_LNK  COLOR_MAGENTA
# define COLOR_FIFO COLOR_YELLOW
# define COLOR_SOCK COLOR_MAGENTA
# define COLOR_BLK  COLOR_BOLD_YELLOW
# define COLOR_CHR  COLOR_BOLD_YELLOW
# define COLOR_EXEC COLOR_RED
# define COLOR_OLNK COLOR_BOLD_GREEN

# ifdef __APPLE__
#  define ST_MTIME st_mtimespec.tv_sec
#  define FT_XATTR_NOFOLLOW 0, XATTR_NOFOLLOW
#  define OWNER_GROUP_SEPARATOR "  "
#  define DATE_SEPARATOR 1
# else
#  define ST_MTIME st_mtime
#  define FT_XATTR_NOFOLLOW 0
#  define OWNER_GROUP_SEPARATOR " "
#  define DATE_SEPARATOR 0
# endif

typedef struct timespec	t_timespec;
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct s_file	t_file;

struct	s_file
{
	char	name[NAME_MAX + 1];
	char	path[PATH_MAX];
	t_stat	stat;
};

struct
{
	uint8_t l		: 1;
	uint8_t r_up	: 1;
	uint8_t a		: 1;
	uint8_t a_up	: 1;
	uint8_t r		: 1;
	uint8_t t		: 1;
	uint8_t u_up	: 1;
	uint8_t g_up	: 1;
} g_flags;

int		parse_flags(int ac, char **av);
t_list	*sort_args(char **fv);
int		lstcmp(const t_list *node1, const t_list *node2);
void	ft_list_msort(t_list **head);
size_t	count_blocks(const t_list *head);
int		print_all(t_list *list, int files_count);
void	print_file(t_list *node, size_t *tab);
void	print_filename(t_file *file);
size_t	*len_max(t_list *node);

#endif
