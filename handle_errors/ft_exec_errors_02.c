/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_errors_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:38:02 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 13:47:26 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_error_onetwosix(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	if (cmd->args && cmd->args[0])
		perror(cmd->args[0]);
	ft_gc_free_all(gc);
	ft_gc_free_all(gc_env);
	rl_clear_history();
	return (126);
}

int	ft_error_onetwoseven(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd->args && cmd->args[0])
		ft_putstr_fd(cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	ft_gc_free_all(gc);
	ft_gc_free_all(gc_env);
	rl_clear_history();
	return (127);
}

char	*ft_access_errors_built_path(char *cmd, char **split_values, t_gc *gc)
{
	if (access(cmd, X_OK) == 0)
		return (ft_gc_free_one(gc, split_values), cmd);
	if (access(cmd, F_OK) == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		ft_gc_free_one(gc, cmd);
		ft_gc_free_one(gc, split_values);
		return ((char *)-1);
	}
	return (NULL);
}

void	ft_access_errors_abs_or_relatif(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	if (access(cmd->args[0], X_OK) != 0)
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putendl_fd(": Permission denied", 2);
			gc->last_status = 126;
		}
		else
		{
			perror(cmd->args[0]);
			gc->last_status = 127;
		}
		ft_gc_free_all(gc);
		ft_gc_free_all(gc_env);
		exit(gc->last_status);
	}
}

void	ft_errors_execve(t_cmd *cmd, char *path, t_gc *gc, t_gc *gc_env)
{
	if (path == (char *)-1)
	{
		gc->last_status = ft_error_onetwosix(cmd, gc, gc_env);
		exit(gc->last_status);
	}
	if (!path)
	{
		gc->last_status = ft_error_onetwoseven(cmd, gc, gc_env);
		exit(gc->last_status);
	}
}
