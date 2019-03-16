/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 20:16:38 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:16:39 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

extern int g_debug;
# define DEBUG(x) if (g_debug) x;
# define DEBUGstr(x) if (g_debug) ft_putstr(x);
# define DEBUGendl(x) if (g_debug) ft_putendl(x);

void	debug_flags(int i);
void	print_node(t_list *node);

#endif
