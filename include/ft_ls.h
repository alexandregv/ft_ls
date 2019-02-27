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
	unsigned int r : 1;
	unsigned int t : 1;
	unsigned int U : 1;
} g_flags;

int		parse_flags(int ac, char **av);
t_list	*sort_args(char **fv);
int		lstcmp(const t_list *node1, const t_list *node2);
void	ft_list_msort(t_list **head);
size_t	count_blocks(const t_list *head);

#endif
