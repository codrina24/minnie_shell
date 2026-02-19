/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:47:47 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:51:56 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_cd(t_cmd *cmd, t_gc *gc, t_env *env)
{
	if (!cmd || !gc || !env)
		return (1);
	if (cmd->args[0] && cmd->args[1] && cmd->args[2])
		return (ft_error_cd(), 1);
	return (ft_cd_execute(cmd, gc, env));
}

int	ft_special_case_env(char *first, t_env *env, t_cmd *cmd)
{
	int	i;

	if (ft_strcmp(first, "env") == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			if (ft_strcmp(cmd->args[i], "env") != 0)
				return (ft_check_env_args(cmd));
			i++;
		}
		return (ft_env(env));
	}
	return (1);
}

int	ft_verify_first_argument(t_cmd *cmd)
{
	char	*first;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NOT_BUILTIN);
	first = cmd->args[0];
	if (ft_strcmp(first, "echo") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "cd") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "pwd") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "env") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "export") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "unset") == 0)
		return (IS_BUILTIN);
	else if (ft_strcmp(first, "exit") == 0)
		return (IS_BUILTIN);
	return (NOT_BUILTIN);
}

int	ft_exec_builtin(t_cmd *cmd, t_env *env, t_gc *gc)
{
	char	*first;

	first = NULL;
	if (!cmd || !cmd->args || !cmd->args[0] || !gc)
	{
		return (1);
	}
	if (cmd && cmd->args && cmd->args[0])
		first = cmd->args[0];
	if (ft_strcmp(first, "cd") == 0)
		return (ft_cd(cmd, gc, env));
	else if (ft_strcmp(first, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(first, "env") == 0)
		return (ft_special_case_env(first, env, cmd));
	else if (ft_strcmp(first, "export") == 0)
		return (ft_export(cmd, env, gc));
	else if (ft_strcmp(first, "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(first, "unset") == 0)
		return (ft_unset(env, cmd, gc));
	return (1);
}
