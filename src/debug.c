/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:18:02 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 14:25:50 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

int	g_debug = 0;

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
	//ft_putstr(" => ");
	//ft_putstr(((t_file *)node->content)->path);
	//ft_putendl(((t_file *)node->content)->name);
	ft_putendl(node->content);
}

void	print_dir(t_list *node)
{
	/*
	*** printf("prev: %s%s | curr: %s%s | next: %s%s\n"
	*** , node->prev ? ((t_file *)node->prev->content)->path : "DEBUT"
	*** , node->prev ? ((t_file *)node->prev->content)->name : ""
	*** , ((t_file *)node->content)->path
	*** , ((t_file *)node->content)->name
	*** , node->next ? ((t_file *)node->next->content)->path : ""
	*** , node->next ? ((t_file *)node->next->content)->name : "FIN"
	*** );
	*/
	printf("%s%s\n", f(node)->path, f(node)->name);
}
