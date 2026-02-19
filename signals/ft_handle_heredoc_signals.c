/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc_signals.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:41:02 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/28 13:32:41 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_mark_it(void)
{
	if (g_signal_received == SIGINT)
	{
		rl_done = 1;
		return (0);
	}
	return (0);
}

void	ft_heredoc_sigint_handler(int signum)
{
	t_gc	*gc;

	(void)signum;
	g_signal_received = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	gc = ft_static_ptr(NULL);
	if (gc)
		gc->last_status = 130;
}

void	ft_setup_signals_heredoc(void)
{
	rl_event_hook = ft_mark_it;
	signal(SIGINT, ft_heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_sigint_close_heredoc(char *line, int write_fd, t_gc *gc)
{
	ft_handle_error_signal(gc);
	gc->last_status = 130;
	if (line)
		ft_gc_free_one(gc, line);
	ft_reset_signals_to_default();
	close(write_fd);
}
