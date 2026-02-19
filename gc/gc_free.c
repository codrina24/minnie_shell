/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:46:03 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/27 18:18:52 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_gc_free_one(t_gc *gc, void *ptr)
{
	t_gc_node	*current;
	t_gc_node	*prev;

	if (!gc)
		return ;
	prev = NULL;
	current = gc->head;
	while (current)
	{
		if (current->tracked_ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				gc->head = current->next;
			free(current->tracked_ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_gc_free_all(t_gc *gc)
{
	t_gc_node	*current;

	if (!gc)
		return ;
	while (gc->head)
	{
		current = gc->head;
		gc->head = gc->head->next;
		if (current->tracked_ptr)
			free(current->tracked_ptr);
		free(current);
	}
	gc->head = NULL;
}

char	*ft_gc_free_tab(t_gc *gc, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (--i >= 0)
	{
		if (tab[i])
			ft_gc_free_one(gc, tab[i]);
	}
	ft_gc_free_one(gc, tab);
	return (NULL);
}

void	ft_gc_free_all_and_env(t_gc *gc, t_gc *gc_env)
{
	if (gc_env)
		ft_gc_free_all(gc_env);
	if (gc)
		ft_gc_free_all(gc);
}

//voir si utile///////////////
void	ft_print_gc_alloc_ptr_for_debug(t_gc *gc)
{
	t_gc_node	*current;
	int			count;

	if (!gc)
	{
		printf("GC is NULL\n");
		return ;
	}
	current = gc->head;
	count = 0;
	while (current)
	{
		printf("Allocation %d: %p\n", count, current->tracked_ptr);
		count++;
		current = current->next;
	}
}
