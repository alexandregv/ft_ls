/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:27:03 by aguiot--          #+#    #+#             */
/*   Updated: 2019/03/16 20:21:09 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
static int	*get_gc_size(void)
{
	static int gc_size = 1;
	return (&gc_size);
}

static void	***get_gc(void)
{
	static void	**gc = NULL;
	return (&gc);
}

void	*ft_smartalloc(size_t size)
{
	void		*mem;
	if (!(mem = malloc(size)))
		return (NULL);
	if (!(*get_gc() = realloc(*get_gc(), sizeof(void *) * (*get_gc_size() + 1))))
		return (NULL);
	get_gc()[*get_gc_size()] = mem;
	*get_gc_size() += 1;
	return (mem);
}

void	ft_smartfree(void)
{
	size_t	i;
	size_t	gc_size;

	i = 0;
	gc_size = *get_gc_size();
	while (i < gc_size)
		free(get_gc()[i++]);
}
*/

void	**g_gc = NULL;
size_t	g_gc_size = 0;

void	*ft_smartalloc(size_t size)
{
	void		*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	if (!(g_gc = realloc(g_gc, sizeof(void *) * (g_gc_size + 1))))
		return (NULL);
	g_gc[g_gc_size++] = mem;
	return (mem);
}

void	ft_smartfree(void)
{
	size_t	i;

	i = 0;
	while (i < g_gc_size)
		free(g_gc[i++]);
	free(g_gc);
}
