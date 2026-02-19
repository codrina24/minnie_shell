/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_extern_commands.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:20:36 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 14:18:06 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_dup_it_v2(int fd_source, int fd_result)
{
	if (dup2(fd_source, fd_result) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_setup(t_ast *ast, int input_fd)
{
	ft_reset_signals_to_default();
	if (input_fd != -1)
	{
		ft_dup_it_v2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (ast->cmd->input_fd != -1)
	{
		ft_dup_it_v2(ast->cmd->input_fd, STDIN_FILENO);
		close(ast->cmd->input_fd);
	}
	if (ast->cmd->output_fd != -1)
	{
		ft_dup_it_v2(ast->cmd->output_fd, STDOUT_FILENO);
		close(ast->cmd->output_fd);
	}
}

void	ft_child_simple(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env)
{
	if (!gc)
		exit (EXIT_FAILURE);
	if (ast->cmd->redir)
	{
		if (ft_open_redir(ast->cmd) != 0)
		{
			ft_clean_resources(gc, gc_env);
			ft_gc_free_all_and_env(gc, gc_env);
			gc->last_status = 1;
			exit(gc->last_status);
		}
	}
	ft_setup(ast, input_fd);
	if ((ast->is_pipe == 1) && ft_verify_first_argument(ast->cmd) == IS_BUILTIN)
	{
		gc->last_status = ft_exec_builtin_cmd(ast, gc, gc_env);
		ft_gc_free_all_and_env(gc, gc_env);
		exit(gc->last_status);
	}
	ft_execve(ast->cmd, gc_env->env, gc, gc_env);
	ft_gc_free_all_and_env(gc, gc_env);
	exit(EXIT_FAILURE);
}

void	ft_parent_simple(int input_fd, pid_t pid, t_gc *gc)
{
	int	status;

	if (input_fd != -1)
	{
		close(input_fd);
	}
	if (waitpid(pid, &status, WUNTRACED) == -1)
	{
		perror("\n");
		status = 1;
		ft_update_last_status(status, gc);
		return ;
	}
	ft_update_last_status(status, gc);
}

void	ft_process_simple(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env)
{
	pid_t	pid;

	if (!ast || !ast->cmd->args[0])
	{
		if (input_fd != -1)
			close(input_fd);
		return ;
	}
	ft_ign_signals();
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
		ft_child_simple(ast, input_fd, gc, gc_env);
	if (ast->is_pipe == 1)
		ft_add_pid(ast, pid);
	else
	{
		ft_setup_signals();
		ft_parent_simple(input_fd, pid, gc);
	}
}
