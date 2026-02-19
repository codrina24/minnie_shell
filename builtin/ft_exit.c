/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:10:54 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:58:30 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_whitespace_and_sign(char *str, int *signe)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*signe = -1;
		i++;
	}
	return (i);
}

int	ft_number_process(char *str, int i, int signe, long long *result)
{
	*result = 0;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		if (*result > (LLONG_MAX / 10))
			return (0);
		if (*result == LLONG_MAX / 10)
		{
			if ((str[i] - '0') > LLONG_MAX % 10)
			{
				if (signe == 1)
					return (0);
				else if ((str[i] - '0') > ((LLONG_MAX % 10) + 1))
					return (0);
			}
		}
		*result = *result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	ft_verify_and_convert_num(char *str, t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	int			i;
	int			sign;
	long long	result;
	long long	rs_result;

	sign = 1;
	if (cmd->args[1])
		str = cmd->args[1];
	i = ft_whitespace_and_sign(str, &sign);
	if (!ft_number_process(str, i, sign, &result))
	{
		ft_error_exit_value(cmd);
		ft_gc_free_all_and_env(gc, gc_env);
		gc->last_status = 2;
		exit(gc->last_status);
	}
	rs_result = sign * result;
	return ((rs_result % 256 + 256) % 256);
}

int	ft_exit(t_cmd *cmd, t_gc *gc, t_gc *gc_env)
{
	if (cmd->args[0])
		ft_putendl_fd("exit", 1);
	if (cmd->args[0] && !cmd->args[1])
	{
		ft_gc_free_all_and_env(gc, gc_env);
		exit(gc->last_status);
	}
	if (cmd->args[1] && cmd->args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	if (cmd->args[1])
		return (ft_verify_and_convert_num(cmd->args[1], cmd, gc, gc_env));
	if (cmd->args[1] && ft_isalpha(cmd->args[1][0]))
	{
		ft_error_exit_value(cmd);
		ft_gc_free_all_and_env(gc, gc_env);
		gc->last_status = 2;
		exit(gc->last_status);
	}
	return (0);
}
