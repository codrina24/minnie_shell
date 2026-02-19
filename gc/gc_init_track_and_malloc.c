/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init_track_and_malloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:46:03 by mzerad            #+#    #+#             */
/*   Updated: 2025/08/07 15:08:26 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_gc_init(t_gc *gc)
{
	gc->head = NULL;
	gc->result = NULL;
	gc->env = NULL;
	gc->flag = 0;
	gc->in_quotes_eof = 0;
}

void	ft_gc_add(t_gc *gc, void *ptr)
{
	t_gc_node	*new;

	if (!gc || !ptr)
		return ;
	new = malloc(sizeof(t_gc_node));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_gc_node));
	new->tracked_ptr = ptr;
	new->next = gc->head;
	gc->head = new;
}

void	*ft_gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	if (!gc || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size);
	ft_gc_add(gc, ptr);
	return (ptr);
}
