/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_errors_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:32:26 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 19:40:39 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_error_null_env(t_gc *gc, t_gc *gc_env)
{
	ft_putstr_fd("ERROR env alloc\n", 2);
	ft_gc_free_all(gc_env);
	ft_gc_free_all(gc);
	rl_clear_history();
	return (1);
}

void	ft_error_cd(void)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
}

void	ft_error_export(const char *input)
{
	if (!input)
		return ;
	ft_putstr_fd("minishell: export : `", 2);
	ft_putstr_fd((char *)input, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	ft_error_stat(char *command_path, char **split_values, t_gc *gc)
{
	ft_putstr_fd(command_path, 2);
	ft_putendl_fd(": Is a directory", 2);
	ft_gc_free_one(gc, command_path);
	ft_gc_free_one(gc, split_values);
}

void	ft_error_heredoc(const char *delim)
{
	char	*text;

	text = "warning: here-document delimited by end-of-file (wanted `";
	write(2, text, ft_strlen(text));
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}
