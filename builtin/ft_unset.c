/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:28:10 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:32:39 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_remove_from_env(t_env *env, t_gc *gc, char *key_to_remove)
{
	if (!key_to_remove)
		return ;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key_to_remove) == 0)
		{
			ft_gc_free_one(gc, env->key);
			env->key = NULL;
			if (env->eq)
			{
				ft_gc_free_one(gc, env->eq);
				env->eq = NULL;
			}
			if (env->value)
			{
				ft_gc_free_one(gc, env->value);
				env->value = NULL;
			}
			return ;
		}
		env = env->next;
	}
}

int	ft_unset(t_env *env, t_cmd *cmd, t_gc *gc)
{
	int	i;

	i = 1;
	if (!env || !cmd || !cmd->args)
		return (1);
	if (cmd->args[0] && !cmd->args[1])
		return (0);
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "unset") == 0)
		{
			while (cmd->args[i])
			{
				ft_remove_from_env(env, gc, cmd->args[i]);
				i++;
			}
		}
	}
	else
		return (1);
	return (0);
}

int	ft_supp_protect(const char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
	{
		perror("failed");
		if (errno == ENOENT)
			return (1);
	}
	return (0);
}
