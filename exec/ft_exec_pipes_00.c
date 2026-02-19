/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipes_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:08:53 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:53:24 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_count_pipes_ast(t_ast *ast)
{
	int	first;
	int	second;

	if (!ast)
		return (0);
	first = ft_count_pipes_ast(ast->first_child);
	second = ft_count_pipes_ast(ast->second_child);
	if (ast->type == PIPE_NODE)
		return (1 + first + second);
	else
		return (first + second);
}

void	ft_share_with(t_ast *ast, pid_t *pids, int *pid_count, int pid_size)
{
	if (!ast)
		return ;
	ast->pids = pids;
	ast->pid_count = pid_count;
	ast->pid_size = pid_size;
	ft_share_with(ast->first_child, pids, pid_count, pid_size);
	ft_share_with(ast->second_child, pids, pid_count, pid_size);
}

void	ft_prepare_shared_package(t_ast *ast, t_gc *gc)
{
	int	count;

	if (!ast)
	{
		return ;
	}
	count = ft_count_pipes_ast(ast);
	if (count < 0)
		count = 0;
	ast->nbr_cmd = count + 1;
	ast->pid_size = ast->nbr_cmd;
	ast->pids = ft_gc_malloc(gc, sizeof(pid_t) * ast->pid_size);
	if (!ast->pids)
	{
		perror("malloc failed");
		return ;
	}
}

void	ft_waitpid(pid_t pid, int *status)
{
	if (waitpid(pid, status, WUNTRACED) == -1)
		perror("waitpid error");
}

int	ft_wait_for_children(t_ast *ast, int pid_count, t_gc *gc)
{
	int	i;
	int	status;
	int	new_line;	

	new_line = 0;
	i = 0;
	while (ast && i < pid_count)
	{
		ft_waitpid(ast->pids[i], &status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT && !new_line)
		{
			write(STDOUT_FILENO, "\n", 1);
			new_line = 1;
		}
		i++;
	}
	ft_update_last_status(status, gc);
	return (status);
}
