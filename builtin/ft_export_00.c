/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:11:50 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:38:02 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

t_env	*ft_init_env_copy(t_gc *gc)
{
	t_env	*node;

	if (!gc)
		return (NULL);
	node = ft_gc_malloc(gc, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->eq = NULL;
	node->value = NULL;
	node->expp = ft_gc_strdup(gc, "export ");
	if (!node->expp)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	ft_copy_from_env(t_gc *gc, t_env *copy, t_env *env)
{
	if (env->key)
	{
		copy->key = ft_gc_strdup(gc, env->key);
		if (!copy->key)
			return (1);
	}
	if (env->eq)
	{
		copy->eq = ft_gc_strdup(gc, env->eq);
		if (!copy->eq)
			return (1);
	}
	if (env->value)
	{
		copy->value = ft_gc_strdup(gc, env->value);
		if (!copy->value)
			return (1);
	}
	return (0);
}

t_env	*ft_copy_env(t_gc *gc, t_env *env)
{
	t_env	*copy;
	t_env	*last;
	t_env	*head;

	head = NULL;
	last = NULL;
	if (!gc)
		return (NULL);
	while (env)
	{
		copy = ft_init_env_copy(gc);
		if (ft_copy_from_env(gc, copy, env) == 1)
			return (NULL);
		if (!head)
			head = copy;
		else
			last->next = copy;
		last = copy;
		env = env->next;
	}
	return (head);
}

int	ft_print_export(t_gc *gc, t_env *env)
{
	if (!env)
		return (1);
	env = ft_copy_env(gc, env);
	ft_bubble_sort(env);
	while (env)
	{
		if (env->key)
		{
			ft_putstr_fd(env->expp, 1);
			ft_putstr_fd(env->key, 1);
			if (env->eq)
			{
				ft_putstr_fd(env->eq, 1);
				if (env->value)
				{
					ft_putstr_fd("\"", 1);
					ft_putstr_fd(env->value, 1);
					ft_putstr_fd("\"", 1);
				}
			}
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_process_export_arg(char *arg, t_env *env, t_gc *gc)
{
	char	*search;
	char	*new_value;
	char	*eq;

	new_value = NULL;
	search = ft_extract_keyy(gc, arg);
	if (!search)
		return (1);
	eq = ft_is_eq(gc, arg);
	if (eq)
	{	
		new_value = ft_get_export_value(gc, arg);
		if (!new_value)
			return (1);
	}
	ft_up_export(env, search, new_value, gc);
	search = NULL;
	new_value = NULL;
	eq = NULL;
	return (0);
}
