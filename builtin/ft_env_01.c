/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:02:27 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:37:42 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_count_env_lines(t_env *env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env)
	{
		if (env->key && env->eq)
			count++;
		env = env->next;
	}
	return (count);
}

char	*ft_build_env_line(t_env *env, t_gc *gc)
{
	char	*line;
	char	*complete_line;

	if (!env || !env->key || !env->eq)
		return (NULL);
	line = ft_gc_strjoin(gc, env->key, env->eq);
	if (!line)
		return (NULL);
	complete_line = ft_gc_strjoin(gc, line, env->value);
	if (!complete_line)
		return (ft_gc_free_one(gc, line), NULL);
	return (complete_line);
}

char	**ft_alloc_env_tab(t_env *env, t_gc *gc)
{
	int		len;
	char	**tab;

	if (!env || !gc)
		return (NULL);
	len = ft_count_env_lines(env);
	tab = ft_gc_malloc(gc, sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_env_tab(t_env *env, t_gc *gc)
{
	char	**tab;
	int		i;
	char	*line;

	if (!env || !gc)
		return (NULL);
	i = 0;
	tab = ft_alloc_env_tab(env, gc);
	if (!tab)
		return (NULL);
	while (env)
	{
		if (env->key && env->eq)
		{
			line = ft_build_env_line(env, gc);
			if (!line)
				return (NULL);
			tab[i++] = line;
		}
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_env(t_env *env)
{
	if (!env)
	{
		return (1);
	}
	while (env)
	{
		if (env->key && env->eq)
			ft_putstr_fd(env->key, 1);
		if (env->key && env->eq)
			ft_putstr_fd(env->eq, 1);
		if (env->key && env->eq && env->value)
			ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (0);
}
