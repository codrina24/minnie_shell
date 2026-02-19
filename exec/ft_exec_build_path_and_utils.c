/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_path_for_execve.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:42:04 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 17:06:21 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

char	*ft_get_path_value_(t_env *env, t_gc *gc)
{
	char	*dup;

	while (env)
	{
		if (env->key && env->value && ft_strcmp(env->key, "PATH") == 0)
		{
			dup = ft_gc_strdup(gc, env->value);
			if (!dup)
				return (NULL);
			return (dup);
		}
		env = env->next;
	}
	return (ft_putstr_fd("PATH environment variable not found\n", 2), NULL);
}

char	**ft_split_path_value(t_env *env, t_gc *gc)
{
	char	*path;
	char	**splitted_path;
	int		j;

	j = 0;
	path = ft_get_path_value_(env, gc);
	if (!path)
		return (NULL);
	splitted_path = ft_gc_split(gc, path, ':');
	if (!splitted_path)
	{
		ft_putstr_fd("Split error\n", 2);
		return (ft_gc_free_one(gc, path), NULL);
	}
	while (splitted_path[j])
	{
		if (splitted_path[j][0] == '\0')
		{
			splitted_path[j] = ft_gc_strdup(gc, ".");
			if (!splitted_path)
				return (NULL);
		}
		j++;
	}
	return (splitted_path);
}

char	*ft_build_complete_path_process(t_env *env, char *command, t_gc *gc)
{
	char		**split_values;
	char		*command_path;
	char		*result;
	struct stat	st;
	int			i;

	i = 0;
	split_values = ft_split_path_value(env, gc);
	if (!split_values)
		return (NULL);
	while (split_values[i])
	{
		command_path = ft_gc_strjoin_cmd(gc, split_values[i], command);
		if (!command_path)
			return (ft_gc_free_one(gc, split_values), NULL);
		if (stat(command_path, &st) == 0 && S_ISDIR(st.st_mode))
			return (ft_error_stat(command_path, split_values, gc), (char *)-1);
		result = ft_access_errors_built_path(command_path, split_values, gc);
		if (result == (char *)-1 || result != NULL)
			return (result);
		ft_gc_free_one(gc, command_path);
		i++;
	}
	return (ft_gc_free_one(gc, split_values), NULL);
}

int	ft_input_is_empty_or_whitespace(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

t_gc	*ft_static_ptr(t_gc *init)
{
	static t_gc	*gc_ptr = NULL;

	if (init != NULL)
		gc_ptr = init;
	return (gc_ptr);
}
