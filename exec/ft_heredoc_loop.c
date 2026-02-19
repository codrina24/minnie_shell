/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:25:39 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 13:27:42 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

char	*ft_expand_in_heredoc(char *line, t_gc *gc, t_gc *gc_env)
{
	char	*expanded;

	expanded = NULL;
	if (gc->in_quotes_eof != 2)
	{
		expanded = ft_expand_token(gc, gc_env->env, line);
		if (!expanded)
		{
			ft_gc_free_one(gc, line);
			ft_reset_signals_to_default();
			return (NULL);
		}
	}
	else
		return (NULL);
	return (expanded);
}

void	ft_write_line(char *line, t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	char	*expanded;
	int		len;

	expanded = ft_expand_in_heredoc(line, gc, gc_env);
	if (expanded)
	{
		len = ft_strlen(expanded);
		write(cmd->write_fd, expanded, len);
	}
	else if (expanded == NULL)
	{
		write(cmd->write_fd, line, ft_strlen(line));
	}
	write(cmd->write_fd, "\n", 1);
}

int	ft_is_delim(char *line, char *delim, t_gc *gc)
{
	if (ft_strcmp(line, delim) == 0)
	{
		if (line)
			ft_gc_free_one(gc, line);
		gc->last_status = 0;
		return (0);
	}
	return (1);
}

int	ft_heredoc_loop(t_cmd *cmd, t_gc *gc, t_gc *gc_env, bool is_child)
{
	char	*line;
	int		rs;

	(void)is_child;
	ft_setup_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		rs = ft_line_and_status_check(line, cmd->write_fd, cmd->input_file, gc);
		if (rs == 1)
			break ;
		else if (rs == 11)
			return (1);
		if (!ft_is_delim(line, cmd->input_file, gc))
			break ;
		ft_write_line(line, cmd, gc, gc_env);
		ft_gc_free_one(gc, line);
	}
	ft_reset_signals_to_default();
	rl_done = 0;
	return (0);
}

int	ft_heredoc_process(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	int	output;

	g_signal_received = 0;
	output = ft_heredoc_loop(cmd, gc, gc_env, false);
	return (output);
}
