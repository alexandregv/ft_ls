#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../include/ft_ls.h"

#define OPT_l options[0]
#define OPT_R options[1]
#define OPT_a options[2]
#define OPT_r options[3]
#define OPT_t options[4]
#define OPTIONS_COUNT 5

int					 parse_options(int ac, char **av, int *options)
{
	int				i;

	i = 0;
	while (i < OPTIONS_COUNT)
		options[i++] = 0;
	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		++av[i];
		while (*av[i])
		{
			OPT_l = (*av[i] == 'l') ? 1 : OPT_l;
			OPT_R = (*av[i] == 'R') ? 1 : OPT_R;
			OPT_a = (*av[i] == 'a') ? 1 : OPT_a;
			OPT_r = (*av[i] == 'r') ? 1 : OPT_r;
			OPT_t = (*av[i] == 't') ? 1 : OPT_t;
			++av[i];
		}
		++i;
	}
	return (i);
}

void				debug_options(int *options, int i)
{
	ft_putstr(" R:");
	ft_putnbr(OPT_R);
	ft_putstr(" l:");
	ft_putnbr(OPT_l);
	ft_putstr(" a:");
	ft_putnbr(OPT_a);
	ft_putstr(" r:");
	ft_putnbr(OPT_r);
	ft_putstr(" t:");
	ft_putnbr(OPT_t);
	ft_putchar('\n');
	ft_putstr(" i:");
	ft_putnbr(i);
	ft_putchar('\n');
	ft_putchar('\n');
}

void		ls_onedir(struct dirent *direntp, int *options)
{
	if (OPT_a)
		ft_putendl(direntp->d_name);
	else if (!OPT_a && direntp->d_name[0] != '.')
		ft_putendl(direntp->d_name);
}

int						 ls(int ac, char **av, int *options)
{
	int				i;
	DIR				*dirp;
	struct		 dirent *direntp;

	if (ac == 0)
	{
		ac = 1;
		//av = (char **)malloc(sizeof(char *)* 2);
		av[0] = ".";
		//av[1] = NULL;
	}
	i = 0;
	while (i < ac)
	{
		dirp = opendir(av[i]);
		if (dirp == NULL)
		{
			perror("ft_ls");
			exit(EXIT_FAILURE);
		}
		if (ac >= 2)
		{
			if (i != 0)
				ft_putchar('\n');
			ft_putstr(av[i]);
			ft_putendl(":");
		}
		while ((direntp = readdir(dirp)))
			ls_onedir(direntp, options);
		closedir(dirp);
		++i;
	}
	//free(av);
	(void)options;
	return (EXIT_SUCCESS);		 
}

int					main(int ac, char **av)
{
	int	 i;
	int				options[5];

	i = parse_options(ac, av, options);
	//debug_options(options, i);
	return(ls(ac-i, av+i, options));
}
