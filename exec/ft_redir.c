/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:48:39 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:55:29 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_file_in(t_cmd *cmd, char *file)
{
	int	infile;

	infile = open(file, O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		cmd->exec_fail = 1;
		return (-1);
	}
	return (infile);
}

int	ft_file_out(t_cmd *cmd, char *file)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		cmd->exec_fail = 1;
		return (-1);
	}
	return (outfile);
}

int	ft_file_out_append(t_cmd *cmd, char *file)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		cmd->exec_fail = 1;
		return (-1);
	}
	return (outfile);
}

int	ft_file_in_heredoc(t_cmd *cmd, char *file)
{
	int	infile;

	infile = open(file, O_RDONLY);
	if (infile == -1)
	{
		perror(file);
		cmd->exec_fail = 1;
		return (-1);
	}
	return (infile);
}

int	ft_open_redir(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (ft_choose_redir(cmd, redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
