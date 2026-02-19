/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:18:22 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 17:20:13 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_prepre_exec(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	int	last_status;
	int	pid_count;

	if (!ast)
		return ;
	pid_count = 0;
	ft_prepare_shared_package(ast, gc);
	ft_share_with(ast, ast->pids, &pid_count, ast->pid_size);
	ft_exec_pipes(ast, -1, gc, gc_env);
	last_status = ft_wait_for_children(ast, pid_count, gc);
	ft_update_last_status(last_status, gc);
	ft_handle_error_signal(gc);
}

void	ft_pipe_node(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == COMMAND_NODE)
		ast->is_pipe = 1;
	else if (ast->type == PIPE_NODE)
	{
		ft_pipe_node(ast->first_child);
		ft_pipe_node(ast->second_child);
	}
}

void	ft_child_pipe(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env)
{
	ft_reset_signals_to_default();
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	dup2(ast->fd[1], STDOUT_FILENO);
	close(ast->fd[0]);
	close(ast->fd[1]);
	if (ast->first_child->type == COMMAND_NODE)
	{
		if (ft_open_redir(ast->first_child->cmd) != 0)
			ft_clean_resources(gc, gc_env);
		ft_child_simple(ast->first_child, -1, gc, gc_env);
	}
	else
		ft_exec_pipes(ast->first_child, -1, gc, gc_env);
	ft_clean_resources(gc, gc_env);
}

void	ft_parent_pipe(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env)
{
	close(ast->fd[1]);
	ft_exec_pipes(ast->second_child, ast->fd[0], gc, gc_env);
	close(ast->fd[0]);
	if (input_fd != -1)
		close(input_fd);
}

void	ft_exec_pipes(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env)
{
	pid_t	pid;

	if (ast->type == PIPE_NODE)
	{
		ft_pipe_node(ast);
		ft_create_pipe(ast->fd);
		ft_ign_signals();
		pid = fork();
		if (pid == -1)
			ft_close_fd(input_fd, ast);
		if (pid == 0)
			ft_child_pipe(ast, input_fd, gc, gc_env);
		else
		{
			ft_add_pid(ast, pid);
			ft_parent_pipe(ast, input_fd, gc, gc_env);
		}
	}
	else if (ast->type == COMMAND_NODE)
	{
		ft_process_simple(ast, input_fd, gc, gc_env);
	}
}
