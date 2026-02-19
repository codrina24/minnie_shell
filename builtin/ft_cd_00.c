/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:38:13 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:15:37 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"
#include "./builtin.h"

char	*ft_get_path_value(t_env *env, char *str, t_gc *gc)
{
	char	*copy;

	if (!env || !str || !gc)
		return (NULL);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, str) == 0)
		{
			if (!env->value || env->value[0] == '\0')
				return (ft_putendl_fd("minishell: cd: HOME not set", 2), NULL);
			copy = ft_gc_strdup(gc, env->value);
			if (!copy)
				return (ft_putstr_fd("Failed to duplicate PATH\n", 2), NULL);
			return (copy);
		}
		env = env->next;
	}
	return (ft_putendl_fd("minishell: cd: ", 2), ft_putendl_fd(str, 2), NULL);
}

t_env	*ft_create_env_node(char *search, char *new_value, t_gc *gc)
{
	t_env	*node;

	if (!search || !new_value || !gc)
		return (NULL);
	node = ft_env_init(gc);
	if (!node)
		return (NULL);
	node->key = ft_gc_strdup(gc, search);
	if (!node->key)
		return (NULL);
	node->eq = ft_gc_strdup(gc, "=");
	if (!node->eq)
		return (NULL);
	node->value = ft_gc_strdup(gc, new_value);
	if (!node->value)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	ft_search_and_update(t_env *env, char *search, char *new_value, t_gc *gc)
{
	if (!env || !search || !new_value || !gc)
		return (1);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, search) == 0)
		{
			if (env->value)
			{
				ft_gc_free_one(gc, env->value);
				env->value = NULL;
			}
			env->value = ft_gc_strdup(gc, new_value);
			if (!env->value)
				return (1);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	ft_up_val(t_env *env, char *search, char *new_value, t_gc *gc)
{
	t_env	*head;
	t_env	*node;

	head = env;
	if (!env || !search || !new_value || !gc)
		return (1);
	if (ft_search_and_update(env, search, new_value, gc) == 0)
		return (0);
	node = ft_create_env_node(search, new_value, gc);
	if (!node)
		return (1);
	ft_env_add_back(head, node);
	return (0);
}

int	ft_up_pwd(t_env *env, char *oldcwd, char *new_path, t_gc *gc)
{
	if (!env || !oldcwd || !new_path || !gc)
		return (1);
	if (ft_up_val(env, "OLDPWD", oldcwd, gc) != 0)
		return (1);
	if (ft_up_val(env, "PWD", new_path, gc) != 0)
		return (1);
	return (0);
}
