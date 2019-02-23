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
# include "../libft/include/libft.h"

typedef struct timespec	t_timespec;
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct s_file	t_file;

extern int	g_options;

struct			s_file
{
	char		name[NAME_MAX + 1];
	char		path[PATH_MAX];
	t_stat		stat;
};

enum	e_flags {
	OPT_l = 0b00000001,
	OPT_R = 0b00000010,
	OPT_a = 0b00000100,
	OPT_r = 0b00000100,
	OPT_t = 0b00001000,
	OPT_U = 0b00010000,
};

int		parse_g_options(int ac, char **av);
#endif
