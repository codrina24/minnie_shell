/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:13:42 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 17:14:41 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
}

void	ft_clean_resources(t_gc *gc, t_gc *gc_env)
{
	ft_gc_free_all(gc);
	ft_gc_free_all(gc_env);
	exit(EXIT_FAILURE);
}

void	ft_close_fd(int input_fd, t_ast *ast)
{
	perror("fork failed");
	close(ast->fd[0]);
	close(ast->fd[1]);
	if (input_fd != -1)
		close(input_fd);
	return ;
}

void	ft_add_pid(t_ast *ast, pid_t pid)
{
	if (ast && ast->pids && ast->pid_count && *(ast->pid_count) < ast->pid_size)
	{
		ast->pids[(*(ast->pid_count))++] = pid;
	}
}
