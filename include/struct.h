/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:40:01 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/18 18:52:43 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

struct
{
	unsigned int	l		: 1;
	unsigned int	r_up	: 1;
	unsigned int	a		: 1;
	unsigned int	a_up	: 1;
	unsigned int	r		: 1;
	unsigned int	t		: 1;
	unsigned int	f		: 1;
	unsigned int	g_up	: 1;
	unsigned int	g		: 1;
	unsigned int	i		: 1;
} g_flags;

#endif
