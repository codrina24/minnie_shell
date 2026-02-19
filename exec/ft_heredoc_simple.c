/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:41:41 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 19:30:03 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_line_and_status_check(char *line, int write_fd, char *delim, t_gc *gc)
{
	if (line == NULL)
	{
		if (g_signal_received != SIGINT)
		{
			ft_error_heredoc(delim);
			if (line)
				ft_gc_free_one(gc, line);
			return (1);
		}
		else
		{
			ft_sigint_close_heredoc(line, write_fd, gc);
			return (11);
		}
	}
	else if (g_signal_received == SIGINT)
	{
		ft_sigint_close_heredoc(line, write_fd, gc);
		return (11);
	}
	return (0);
}

int	ft_create_temp_file(t_cmd *cmd, t_gc *gc)
{
	char	*pid_str;
	char	*count_str;
	char	*name_sec;
	pid_t	pid;

	pid = getpid();
	pid_str = ft_gc_itoa(gc, pid);
	if (!pid_str)
		return (-1);
	count_str = ft_gc_itoa(gc, cmd->fd_count);
	if (!count_str)
		return (ft_gc_free_one(gc, pid_str), -1);
	name_sec = ft_gc_strjoin(gc, "temp_", pid_str);
	ft_gc_free_one(gc, pid_str);
	if (!name_sec)
		return (ft_gc_free_one(gc, count_str), -1);
	cmd->temp_fd = ft_gc_strjoin(gc, name_sec, count_str);
	ft_gc_free_one(gc, count_str);
	if (!cmd->temp_fd)
		return (-1);
	cmd->fd_count++;
	return (0);
}

void	ft_failed_heredoc_process(t_cmd *cmd)
{
	close(cmd->write_fd);
	unlink(cmd->temp_fd);
	cmd->input_fd = -1;
	g_signal_received = 0;
}

void	ft_success_heredoc_process(t_cmd *cmd)
{
	close(cmd->write_fd);
	cmd->input_file = cmd->temp_fd;
	cmd->input_fd = ft_file_in_heredoc(cmd, cmd->input_file);
	unlink(cmd->temp_fd);
	cmd->temp_fd = NULL;
}

int	ft_handle_heredoc(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	while (cmd->redir)
	{
		if (cmd->redir->type == HEREDOC)
		{
			if (ft_create_temp_file(cmd, gc) == -1)
				return (-1);
			cmd->write_fd = open(cmd->temp_fd, O_WRONLY
					| O_CREAT | O_TRUNC, 0600);
			if (cmd->write_fd == -1)
				return (-1);
			if (ft_heredoc_process(cmd, gc, gc_env) == 1)
			{
				ft_failed_heredoc_process(cmd);
				return (1);
			}
			ft_success_heredoc_process(cmd);
		}
		cmd->redir = cmd->redir->next;
	}
	return (0);
}
