#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"

# include "debug.h"

# define COLOR_RESET       "\e[0m"
# define COLOR_BOLD_BLUE   "\e[1;94m"
# define COLOR_CYAN        "\e[36m"
# define COLOR_YELLOW      "\e[33m"
# define COLOR_MAGENTA     "\e[35m"
# define COLOR_BOLD_YELLOW "\e[1;33m"
# define COLOR_BOLD_GREEN  "\e[1;32m"
# define COLOR_RED         "\e[36m"

# define COLOR_DIR  COLOR_BOLD_BLUE
# define COLOR_LNK  COLOR_CYAN
# define COLOR_FIFO COLOR_YELLOW
# define COLOR_SOCK COLOR_MAGENTA
# define COLOR_BLK  COLOR_BOLD_YELLOW
# define COLOR_CHR  COLOR_BOLD_YELLOW
# define COLOR_EXEC COLOR_BOLD_GREEN
# define COLOR_OLNK COLOR_RED

# ifdef _DARWIN_FEATURE_64_BIT_INODE
#  define ST_MTIME st_mtimespec.tv_sec
# else
#  define ST_MTIME st_mtime
# endif

typedef struct timespec	t_timespec;
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct s_file	t_file;

struct			s_file
{
	char		name[NAME_MAX + 1];
	char		path[PATH_MAX];
	t_stat		stat;
};

struct {
	unsigned int l : 1;
	unsigned int R : 1;
	unsigned int a : 1;
	unsigned int A : 1;
	unsigned int r : 1;
	unsigned int t : 1;
	unsigned int U : 1;
	unsigned int G : 1;
} g_flags;

int		parse_flags(int ac, char **av);
t_list	*sort_args(char **fv);
int		lstcmp(const t_list *node1, const t_list *node2);
void	ft_list_msort(t_list **head);
size_t	count_blocks(const t_list *head);
int		print_all(t_list *list, int files_count);
void	print_file(t_list *node);
void	print_filename(t_file *file);

#endif
