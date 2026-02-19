/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:48:16 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:54:30 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_check_execve_args_or_exit(t_gc *gc, t_gc *gc_env, t_cmd *cmd)
{
	if (!gc || !cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
	{
		if (gc)
			gc->last_status = 127;
		ft_gc_free_all(gc);
		ft_gc_free_all(gc_env);
		exit(127);
	}
}

char	**ft_get_env_or_exit(t_env *envp, t_gc *gc, t_gc *gc_env)
{
	char	**env;

	env = ft_env_tab(envp, gc);
	if (!env)
	{
		ft_error_null_env(gc, gc_env);
		exit(1);
	}
	return (env);
}

void	ft_execve_direct_path(t_gc *gc, t_gc *gc_env, t_cmd *cmd, char **env)
{
	struct stat	st;

	if (stat(cmd->args[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell$: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putendl_fd(": Is a directory", 2);
			gc->last_status = 126;
			ft_gc_free_all(gc);
			ft_gc_free_all(gc_env);
			exit(126);
		}
	}
	if (access(cmd->args[0], X_OK) != 0)
		ft_access_errors_abs_or_relatif(cmd, gc, gc_env);
	if (execve(cmd->args[0], cmd->args, env) == -1)
	{
		gc->last_status = ft_error_onetwosix(cmd, gc, gc_env);
		exit(gc->last_status);
	}
}

void	ft_execve(t_cmd *cmd, t_env *envp, t_gc *gc, t_gc *gc_env)
{
	char	*path;
	char	**env;

	ft_check_execve_args_or_exit(gc, gc_env, cmd);
	env = ft_get_env_or_exit(envp, gc, gc_env);
	if (cmd->args[0][0] == '/' || (ft_strncmp(cmd->args[0], "./", 2) == 0)
		|| (ft_strncmp(cmd->args[0], "../", 3) == 0))
		ft_execve_direct_path(gc, gc_env, cmd, env);
	else
	{
		path = ft_build_complete_path_process(envp, cmd->args[0], gc);
		ft_errors_execve(cmd, path, gc, gc_env);
		if (execve(path, cmd->args, env) == -1)
		{
			gc->last_status = ft_error_onetwosix(cmd, gc, gc_env);
			exit(gc->last_status);
		}
	}
}

int	ft_choose_redir(t_cmd *cmd, t_redir *redir)
{
	if (redir->type == REDIN)
	{
		cmd->input_fd = ft_file_in(cmd, redir->file);
		if (cmd->input_fd == -1 && cmd->exec_fail == 1)
			return (1);
	}
	else if (redir->type == REDOUT)
	{
		cmd->output_fd = ft_file_out(cmd, redir->file);
		if (cmd->output_fd == -1 && cmd->exec_fail == 1)
			return (1);
	}
	else if (redir->type == APPEND)
	{
		cmd->output_fd = ft_file_out_append(cmd, redir->file);
		if (cmd->output_fd == -1 && cmd->exec_fail == 1)
			return (1);
	}
	return (0);
}
