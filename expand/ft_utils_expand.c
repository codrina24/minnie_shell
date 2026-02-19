/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:10:36 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:11:38 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

bool	ft_pars_is_or(t_token *token)
{
	return (token->type == REDIN || token->type == REDOUT
		|| token->type == APPEND || token->type == HEREDOC);
}

char	*ft_get_env_value(t_env *env, const char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, (char *)key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ft_expand_exit_status(t_gc *gc, int i)
{
	char	*status;

	status = ft_gc_itoa(gc, gc->last_status);
	if (!status)
	{
		return (-1);
	}
	gc->result = ft_gc_strjoin(gc, gc->result, status);
	if (!gc->result)
		return (ft_gc_free_one(gc, status), -1);
	ft_gc_free_one(gc, status);
	return (i + 2);
}

int	ft_missing_env_val(char *env_val, char *var_name, t_gc *gc)
{
	ft_gc_free_one(gc, var_name);
	env_val = ft_gc_strdup(gc, "");
	if (!env_val)
		return (-1);
	return (-1);
}
