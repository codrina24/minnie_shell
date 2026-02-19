/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_errors_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:18:57 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 19:40:09 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_check_env_args(t_cmd *cmd)
{
	if (cmd->args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (1);
	}
	return (0);
}

void	ft_error_exit_value(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_another_error(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	if (cmd->args && cmd->args[0])
		perror(cmd->args[0]);
	ft_gc_free_all(gc);
	ft_gc_free_all(gc_env);
	rl_clear_history();
	return (127);
}
