/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals_00.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:44:55 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/28 13:50:31 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_handle_error_signal(t_gc *gc)
{
	if (g_signal_received != 0)
	{
		gc->last_status = 128 + g_signal_received;
		g_signal_received = 0;
		return (gc->last_status);
	}
	return (0);
}

void	ft_sigint_handler(int signum)
{
	t_gc	*gc;

	gc = ft_static_ptr(NULL);
	g_signal_received = signum;
	gc->last_status = 130;
	write(1, "\n", 1);
	if (gc && gc->flag == 1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
}

void	ft_update_last_status(int status, t_gc *gc)
{
	int	signum;
	int	len;
	int	second_len;

	len = ft_strlen("Quit (core dumped)\n");
	second_len = ft_strlen("Segmentation fault (core dumped)\n");
	if (WIFEXITED(status))
		gc->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		gc->last_status = 128 + signum;
		if (signum == SIGQUIT)
			write(2, "Quit (core dumped)\n", len);
		else if (signum == SIGSEGV)
			write(2, "Segmentation fault (core dumped)\n", second_len);
	}
	else
		gc->last_status = 1;
	g_signal_received = 0;
}
