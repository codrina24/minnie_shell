/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_exec_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:51:00 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/24 18:01:36 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_exec_cmd_node(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	int	status;

	if (ast->cmd->redir && ast->cmd->redir->type == HEREDOC)
	{
		if (ft_handle_heredoc(ast->cmd, gc, gc_env) == 1)
			return (1);
	}
	if (ft_open_redir(ast->cmd) != 0)
	{
		gc->last_status = 1;
		return (gc->last_status);
	}
	if (ft_verify_first_argument(ast->cmd) == IS_BUILTIN)
	{
		status = ft_exec_builtin_cmd(ast, gc, gc_env);
		return (status);
	}
	ft_process_simple(ast, -1, gc, gc_env);
	return (gc->last_status);
}

int	ft_exec_pipe_node(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	(void)gc_env;
	if (!ast)
		return (1);
	if (ft_prep_heredoc(ast, gc, gc_env) == 1)
		return (1);
	ft_prepre_exec(ast, gc, gc_env);
	return (gc->last_status);
}

int	ft_exec_and_node(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	if (!ast)
		return (1);
	ft_exec(ast->first_child, gc, gc_env);
	if (gc->last_status == 0)
		ft_exec(ast->second_child, gc, gc_env);
	return (gc->last_status);
}

int	ft_exec_option_node(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	if (!ast)
		return (1);
	ft_exec(ast->first_child, gc, gc_env);
	if (gc->last_status != 0)
		ft_exec(ast->second_child, gc, gc_env);
	return (gc->last_status);
}

int	ft_exec(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	static t_exec	exec_table[]
		= {
	{COMMAND_NODE, ft_exec_cmd_node},
	{PIPE_NODE, ft_exec_pipe_node},
	{AND_NODE, ft_exec_and_node},
	{OPTION_NODE, ft_exec_option_node},
	{-1, NULL}
	};
	int				i;

	if (!gc || !gc_env)
		return (1);
	i = 0;
	if (!ast)
	{
		gc->last_status = 0;
		return (0);
	}
	while (exec_table[i].type != -1)
	{
		if (exec_table[i].type == ast->type)
			return (exec_table[i].callback(ast, gc, gc_env));
		i++;
	}
	return (gc->last_status);
}
