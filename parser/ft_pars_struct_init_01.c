/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_struct_init_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:32:13 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 18:01:54 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_minishell.h"

t_ast	*ft_pars_new_command_node(t_cmd *cmd, t_gc *gc)
{
	t_ast	*node;

	node = ft_gc_malloc(gc, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->type = COMMAND_NODE;
	node->pids = NULL;
	node->pid_count = NULL;
	node->pid_size = 0;
	node->is_pipe = 0;
	node->first_child = NULL;
	node->second_child = NULL;
	return (node);
}

t_ast	*ft_new_ast_node(t_ast *first, t_ast *second, int magic_nbr, t_gc *gc)
{
	t_ast	*node;

	node = ft_gc_malloc(gc, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->type = magic_nbr;
	node->nbr_cmd = 0;
	node->first_child = first;
	node->second_child = second;
	return (node);
}

int	ft_pars_find_len_without_or_list(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (ft_pars_is_or(token))
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		count++;
		token = token->next;
	}
	return (count);
}
