/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:33:23 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 17:38:29 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_heredoc_child(t_cmd *cmd, int *fd, t_gc *gc, t_gc *gc_env)
{
	close(fd[0]);
	cmd->write_fd = fd[1];
	if (ft_heredoc_loop(cmd, gc, gc_env, true) == 1)
	{
		ft_gc_free_all_and_env(gc, gc_env);
		gc->last_status = 130;
		close(fd[1]);
		exit(gc->last_status);
	}
	close(fd[1]);
	ft_gc_free_all_and_env(gc, gc_env);
	exit(EXIT_SUCCESS);
}

int	ft_catch_parent_status(int *fd, int status, t_gc *gc)
{
	ft_update_last_status(status, gc);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (0);
	}
	if (gc->last_status != 0 && g_signal_received != SIGINT)
	{
		close(fd[0]);
		return (1);
	}
	return (0);
}

int	ft_handle_heredoc_pipe(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		output;

	if (pipe(fd) == -1)
		return (1);
	ft_ign_signals();
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
		ft_heredoc_child(cmd, fd, gc, gc_env);
	close(fd[1]);
	waitpid(pid, &status, 0);
	output = ft_catch_parent_status(fd, status, gc);
	if (output != 0)
		return (output);
	cmd->input_fd = fd[0];
	return (0);
}

int	ft_handle_heredoc_redir(t_ast *ast, t_redir *redir, t_gc *gc, t_gc *gc_env)
{
	if (redir->type == HEREDOC)
	{
		ast->cmd->redir = redir;
		ast->cmd->delim = ft_gc_strdup(gc, redir->file);
		if (!ast->cmd->delim)
			return (1);
		if (ft_handle_heredoc_pipe(ast->cmd, gc, gc_env) != 0)
			return (ft_gc_free_one(gc, ast->cmd->delim), gc->last_status);
	}
	return (0);
}

int	ft_prep_heredoc(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	int		output;
	t_redir	*redir;

	if (ast->type == COMMAND_NODE && ast->cmd && ast->cmd->redir)
	{
		redir = ast->cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				output = ft_handle_heredoc_redir(ast, redir, gc, gc_env);
				if (output != 0)
					return (output);
			}
			redir = redir->next;
		}
	}
	else if (ast->type == PIPE_NODE)
	{
		if (ft_prep_heredoc(ast->first_child, gc, gc_env))
			return (1);
		if (ft_prep_heredoc(ast->second_child, gc, gc_env))
			return (1);
	}
	return (0);
}
