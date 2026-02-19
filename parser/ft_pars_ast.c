/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:27:47 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:30:14 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_minishell.h"

t_token	*ft_find_this_token(t_token *token, int magic_nbr)
{
	while (token && token->type != magic_nbr)
		token = token->next;
	return (token);
}

t_ast	*ft_create_first_node(t_cmd *cmd, t_gc *gc)
{
	t_ast	*first;

	first = ft_pars_new_command_node(cmd, gc);
	if (!first)
		return (ft_gc_free_one(gc, cmd), NULL);
	return (first);
}

t_ast	*ft_create_team(t_token *next, t_ast *first, int magic_nbr, t_gc *gc)
{
	t_cmd	*second_cmd;
	t_ast	*second;
	t_ast	*node_type;

	second_cmd = ft_pars_extracted_command_list(next, gc);
	if (!second_cmd)
		return (first);
	second = ft_create_ast(second_cmd, gc);
	if (!second)
		return (first);
	node_type = ft_new_ast_node(first, second, magic_nbr, gc);
	if (!node_type)
	{
		return (NULL);
	}
	return (node_type);
}

t_ast	*ft_create_ast(t_cmd *cmd, t_gc *gc)
{
	t_ast	*first;
	t_token	*pipe;
	t_token	*and;
	t_token	*option;

	if (!cmd || !gc)
		return (NULL);
	pipe = ft_find_this_token(cmd->token, PIPE);
	and = ft_find_this_token(cmd->token, AND);
	option = ft_find_this_token(cmd->token, OPTION);
	first = ft_create_first_node(cmd, gc);
	if (!first)
		return (NULL);
	if (and)
		return (ft_create_team(and->next, first, AND_NODE, gc));
	else if (option)
		return (ft_create_team(option->next, first, OPTION_NODE, gc));
	else if (pipe)
		return (ft_create_team(pipe->next, first, PIPE_NODE, gc));
	return (first);
}
