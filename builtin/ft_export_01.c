/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:18:24 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:38:39 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

t_env	*ft_create_exp_node(char *key, char *value, t_gc *gc)
{
	t_env	*node;

	node = ft_env_init(gc);
	if (key)
	{
		node->key = ft_gc_strdup(gc, key);
		if (!node->key)
		{
			node->key = ft_gc_strdup(gc, "");
			if (!node->key)
				return (NULL);
		}
	}
	if (value)
	{
		node->eq = ft_gc_strdup(gc, "=");
		if (!node->eq)
			return (NULL);
		node->value = ft_gc_strdup(gc, value);
		if (!node->value)
			return (NULL);
	}
	return (node);
}

void	ft_up_export(t_env *env, char *key, char *value, t_gc *gc)
{
	t_env	*node;
	t_env	*head;

	head = env;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
		{
			ft_clean_value(env, gc);
			if (value)
			{
				env->eq = ft_gc_strdup(gc, "=");
				env->value = ft_gc_strdup(gc, value);
				if (!env->eq || !env->value)
					return ;
			}
			return ;
		}
		env = env->next;
	}
	node = ft_create_exp_node(key, value, gc);
	if (!node)
		return ;
	ft_env_add_back(head, node);
}

char	*ft_get_export_value(t_gc *gc, char *str)
{
	int		i;
	int		start;
	char	*new_value;

	i = 0;
	start = 0;
	new_value = NULL;
	if (!str || !gc)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
			start = i + 1;
		i++;
	}
	if (start == 0)
		new_value = ft_gc_strdup(gc, "");
	else
	{
		new_value = ft_gc_substr(gc, str, start, i - start);
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}

char	*ft_is_eq(t_gc *gc, const char *input)
{
	int		i;
	char	*eq;

	i = 0;
	while (input[i])
	{
		if (input[i] == '=')
		{
			eq = ft_gc_strdup(gc, "=");
			if (!eq)
				return (NULL);
			return (eq);
		}
		i++;
	}
	return (NULL);
}

char	*ft_extract_keyy(t_gc *gc, const char *input)
{
	char	*key;
	size_t	i;

	i = 0;
	if (ft_isdigit(input[0])
		|| (!ft_isalnum(input[0]) && input[0] != '_' && input[0] != '$'))
		return (ft_error_export(input), NULL);
	while (input[i] && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (ft_error_export(input), NULL);
		i++;
	}
	if (i == 0)
		return (ft_error_export(input), NULL);
	key = ft_gc_malloc(gc, i + 1);
	if (!key)
	{
		return (NULL);
	}
	ft_strlcpy(key, input, i + 1);
	return (key);
}
