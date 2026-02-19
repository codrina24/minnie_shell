/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:48:55 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 16:23:18 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_search_n(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	ft_n_options(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return (1);
	i = 1;
	while (i >= 1 && cmd->args[i])
	{
		if (ft_search_n(cmd->args[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

void	ft_print_without_option(t_cmd *cmd)
{
	int		i;
	int		j;
	char	**args;
	char	*last;

	i = 1;
	if (!cmd || !cmd->args)
		return ;
	args = cmd->args;
	while (args[i])
		i++;
	if (i >= 1 && args[i - 1])
		last = args[i - 1];
	if (i >= 2)
		i = i - 2;
	j = 1;
	while (j <= i && args[j])
	{
		printf("%s ", args[j]);
		j++;
	}
	if (last)
		printf("%s\n", last);
}

void	ft_print_with_option(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = ft_n_options(cmd);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i] && cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int		start;
	char	**args;

	if (!cmd || !cmd->args)
		return (1);
	args = cmd->args;
	start = ft_n_options(cmd);
	if (!args[1])
		return (write(1, "\n", 1), 0);
	if (start > 1)
	{
		ft_print_with_option(cmd);
		return (0);
	}
	else
	{
		ft_print_without_option(cmd);
		return (0);
	}
}
