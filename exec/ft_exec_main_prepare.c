/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_main_prepare.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:52:25 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 13:06:02 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_check_tty(void)
{
	int	result;

	result = isatty(STDIN_FILENO);
	if (result < 0)
	{
		ft_putstr_fd("error\n", 2);
		return (1);
	}
	return (0);
}

char	*ft_copy_input(void)
{
	char	*input;

	rl_done = 0;
	ft_static_ptr(NULL)->flag = 1;
	input = readline("minishell$ ");
	ft_static_ptr(NULL)->flag = 2;
	if (!input)
		write(1, "exit\n", 5);
	else if (g_signal_received == SIGINT)
	{
		if (input)
			free(input);
		return (ft_itoa(130));
	}
	add_history(input);
	return (input);
}

int	ft_handle_input(char *input, t_gc *gc)
{
	int	lex_status;
	int	sig_status;

	if (!input || ft_input_is_empty_or_whitespace(input))
		return (1);
	lex_status = ft_check_lex_and_handle_if_error(input, gc);
	if (lex_status != 0)
		return (2);
	sig_status = ft_handle_error_signal(gc);
	if (sig_status != 0 && sig_status != SIGINT)
		return (3);
	ft_reset_signals_to_default();
	return (0);
}

static void	ft_free_input_and_gc(char *input, t_gc *gc)
{
	if (input)
	{
		free(input);
	}
	ft_gc_free_all(gc);
}

int	ft_mini_world(t_env *env, t_ast **ast, t_gc *gc, t_gc *gc_env)
{
	char	*input;
	int		status;

	ft_static_ptr(gc);
	while (1)
	{
		g_signal_received = 0;
		ft_setup_signals();
		ft_gc_init(gc);
		input = ft_copy_input();
		if (!input)
			break ;
		status = ft_handle_input(input, gc);
		if (status == 0)
		{
			if (ft_pre_exec(env, input, ast, gc) == 0 && *ast)
				ft_exec(*ast, gc, gc_env);
		}
		else if (status == -1)
			return (ft_safe_return(gc, gc_env, -1));
		ft_free_input_and_gc(input, gc);
	}
	return (gc->last_status);
}
