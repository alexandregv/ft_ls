#ifndef FTLS_H
# define FTLS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "../libft/include/libft.h"

typedef struct timespec t_timespec;
typedef struct stat t_stat;
typedef struct s_file t_file;

struct			s_file
{
	char		name[NAME_MAX + 1];
	char		path[PATH_MAX];
	t_stat		stat;
	t_file		*next;
};

#endif
