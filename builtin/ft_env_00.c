/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:58:55 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:56:36 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_isuppernum(int c)
{
	unsigned char	x;

	x = c;
	if ((x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9'))
		return (1);
	return (0);
}

void	ft_increment_shlvl(t_gc *gc, t_env *env)
{
	int	count;

	count = 0;
	if (!gc || !env)
		return ;
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			count = ft_atoi(env->value);
			if (!count)
				return ;
			count++;
			ft_gc_free_one(gc, env->value);
			env->value = NULL;
			env->value = ft_gc_itoa(gc, count);
			if (!env->value)
				return ;
			return ;
		}
		env = env->next;
	}	
}

char	*ft_extract_key(t_gc *gc, const char *input)
{
	char	*key;
	size_t	i;

	i = 0;
	if (!gc || !input)
		return (NULL);
	if (ft_isdigit(input[0]))
		return (NULL);
	while (input[i] && (ft_isuppernum(input[i])
			|| input[i] == '_'))
		i++;
	key = ft_gc_malloc(gc, i + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, input, i + 1);
	return (key);
}

t_env	*ft_create_env_struct(char *input, t_gc *gc)
{
	t_env	*env;
	char	*value;

	env = ft_env_init(gc);
	if (!env || !gc)
		return (NULL);
	env->key = ft_extract_key(gc, input);
	if (!env->key || env->key[0] == '\0')
		return (NULL);
	env->eq = ft_is_eq(gc, input);
	if (!env->eq)
		return (NULL);
	value = getenv(env->key);
	if (value)
		env->value = ft_gc_strdup(gc, value);
	else
	{
		env->value = ft_gc_strdup(gc, "");
	}
	if (!env->value)
		return (NULL);
	return (env);
}

t_env	*ft_create_env_list(char **envp, t_env *env, t_gc *gc)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	if (!gc)
		return (NULL);
	if (!envp)
		return (ft_putstr_fd("minishell: env not found\n", STDERR_FILENO), NULL);
	i = 0;
	while (envp[i])
	{
		node = ft_create_env_struct(envp[i], gc);
		if (node)
		{
			env = ft_env_add_back(env, node);
			if (!env)
				return (NULL);
		}
		i++;
	}
	return (env);
}
