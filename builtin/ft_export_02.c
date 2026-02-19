/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:25:06 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:39:45 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_swap_key(t_env *env)
{	
	char	*temp;

	if (!env)
		return ;
	temp = env->key;
	env->key = env->next->key;
	env->next->key = temp;
}

void	ft_swap_value(t_env *env)
{
	char	*temp;

	if (!env)
		return ;
	temp = env->value;
	env->value = env->next->value;
	env->next->value = temp;
}

void	ft_bubble_sort(t_env *env)
{
	t_env	*current;
	bool	swapped;

	if (!env)
		return ;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		current = env;
		while (current && current->next)
		{
			if ((current->key && current->next->key)
				&& (ft_strcmp(current->key, current->next->key) > 0))
			{
				ft_swap_key(current);
				ft_swap_value(current);
				swapped = true;
			}
			current = current->next;
		}
		if (swapped == false)
			break ;
	}
}

void	ft_clean_value(t_env *env, t_gc *gc)
{
	if (!env || !gc)
		return ;
	ft_gc_free_one(gc, env->eq);
	ft_gc_free_one(gc, env->value);
	env->eq = NULL;
	env->value = NULL;
}

int	ft_export(t_cmd *cmd, t_env *env, t_gc *gc)
{
	int	i;

	if (!cmd || !env || !gc)
		return (1);
	if (!cmd->args[1])
		return (ft_print_export(gc, env), 0);
	i = 1;
	while (cmd->args[i])
	{
		if (ft_process_export_arg(cmd->args[i], env, gc))
			return (1);
		i++;
	}
	return (0);
}
