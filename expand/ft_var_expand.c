/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:12:04 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:13:04 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_expand_env_var(t_gc *gc, t_env *env, const char *input, int i)
{
	char	*var_name;
	char	*env_val;
	int		len;

	i++;
	var_name = ft_extract_key(gc, &input[i]);
	if (!var_name)
	{
		return (-1);
	}
	len = ft_strlen(var_name);
	env_val = ft_get_env_value(env, var_name);
	if (!env_val)
		return (ft_missing_env_val(env_val, var_name, gc));
	if (env_val)
	{
		gc->result = ft_gc_strjoin(gc, gc->result, env_val);
		if (!gc->result)
			return (ft_gc_free_one(gc, var_name), -1);
	}
	i += len;
	ft_gc_free_one(gc, var_name);
	return (i);
}

int	ft_expand_dollar(t_gc *gc, t_env *env, const char *input, int i)
{
	int	status;
	int	status_second;

	if (input[i] && input[i + 1] && input[i + 1] == '?')
	{
		status = ft_expand_exit_status(gc, i);
		if (!status)
			return (-1);
		return (status);
	}
	else if ((input[i] && input[i + 1])
		&& (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
	{
		status_second = ft_expand_env_var(gc, env, input, i);
		if (!status_second)
			return (-1);
		return (status_second);
	}
	else
	{
		gc->result = ft_gc_strjoin(gc, gc->result, "$");
		if (!gc->result)
			return (-1);
		return (i + 1);
	}
}

char	*ft_expand_process(t_gc *gc, t_env *env, const char *input)
{
	char	tmp[2];
	int		i;

	i = 0;
	if (!gc || !input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && !ft_is_in_single_quotes(input, i))
		{
			i = ft_expand_dollar(gc, env, input, i);
			if (i == -1)
				return (ft_gc_free_one(gc, gc->result), NULL);
			continue ;
		}
		tmp[0] = input[i];
		tmp[1] = '\0';
		gc->result = ft_gc_strjoin(gc, gc->result, tmp);
		if (!gc->result)
			return (ft_gc_free_one(gc, gc->result), NULL);
		i++;
	}
	return (gc->result);
}

char	*ft_expand_token(t_gc *gc, t_env *env, const char *input)
{
	if (!gc || !input)
		return (NULL);
	gc->result = ft_gc_strdup(gc, "");
	if (!gc->result)
		return (NULL);
	if (!ft_expand_process(gc, env, input))
	{
		return (ft_gc_free_one(gc, gc->result), NULL);
	}
	return (gc->result);
}
