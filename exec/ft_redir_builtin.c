/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:01:51 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 18:03:14 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_lets_dup(int *original_stdout, int *original_stdin)
{
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdout == -1)
		return (perror("dup stdout"), 1);
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
		return (perror("dup stdin"), close(*original_stdout), 1);
	return (0);
}

int	ft_dup2_in_builtin(t_cmd *cmd)
{
	if (cmd->output_fd != -1)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			return (-1);
		close(cmd->output_fd);
	}
	if (cmd->input_fd != -1)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			return (-1);
		close(cmd->input_fd);
	}
	return (0);
}

void	ft_restore_fds(int original_stdout, int original_stdin)
{
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		perror("restore: stdout");
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		perror("restore: stdin");
	close(original_stdout);
	close(original_stdin);
}

void	ft_centralize_errors(char x, int original_stdout, int original_stdin)
{
	if (x == 'w')
		perror("dup origin");
	else if (x == 'y')
	{
		perror("dup2_in_builtin");
		ft_restore_fds(original_stdout, original_stdin);
	}
	else if (x == 'z')
	{
		ft_putstr_fd("Error\n", 2);
		ft_restore_fds(original_stdout, original_stdin);
	}
}

int	ft_exec_builtin_with_redir(t_cmd *cmd, t_env *env, t_gc *gc, t_gc *gc_env)
{
	int	original_stdout;
	int	original_stdin;
	int	status;

	ft_reset_signals_to_default();
	if (ft_lets_dup(&original_stdout, &original_stdin) != 0)
		return (1);
	if (original_stdout == -1 || original_stdin == -1)
		return (ft_centralize_errors('w', original_stdout, original_stdin), 1);
	if (ft_dup2_in_builtin(cmd) == -1)
		return (ft_centralize_errors('y', original_stdout, original_stdin), 1);
	status = ft_exec_builtin(cmd, env, gc_env);
	if (status == -1)
		return (ft_centralize_errors('z', original_stdout, original_stdin), 1);
	if (g_signal_received)
	{
		gc->last_status = 128 + g_signal_received;
		g_signal_received = 0;
	}
	else
		ft_update_last_status(status, gc_env);
	ft_restore_fds(original_stdout, original_stdin);
	return (gc->last_status);
}
