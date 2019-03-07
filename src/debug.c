#include "ft_ls.h"

int	g_debug = 1;

void	debug_flags(int i)
{
	ft_putstr(" R:");
	ft_putnbr(g_flags.r_up);
	ft_putstr(" l:");
	ft_putnbr(g_flags.l);
	ft_putstr(" a:");
	ft_putnbr(g_flags.a);
	ft_putstr(" A:");
	ft_putnbr(g_flags.a_up);
	ft_putstr(" r:");
	ft_putnbr(g_flags.r);
	ft_putstr(" t:");
	ft_putnbr(g_flags.t);
	ft_putstr(" U:");
	ft_putnbr(g_flags.u_up);
	ft_putchar('\n');
	ft_putstr(" i:");
	ft_putnbr(i);
	ft_putchar('\n');
	ft_putchar('\n');
}

void	print_node(t_list *node)
{
	ft_putstr(" => ");
	ft_putstr(((t_file *)node->content)->path);
	ft_putendl(((t_file *)node->content)->name);
}
