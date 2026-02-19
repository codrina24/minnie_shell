/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:27:16 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 17:59:09 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_get_cmd_file(t_token *token, t_redir *redir, t_cmd *cmd)
{
	if (token->type == REDIN || token->type == HEREDOC)
	{
		cmd->input_file = redir->file;
		return (0);
	}
	else if (token->type == REDOUT || token->type == APPEND)
	{
		cmd->output_file = redir->file;
		return (0);
	}
	return (1);
}

bool	ft_valid_redir_process(t_token *token, t_cmd *cmd, t_gc *gc)
{
	t_redir	*redir;

	if (token && token->next && token->next->type == WORD)
	{
		redir = ft_new_or(token->type, token->next->value, gc);
		if (!redir)
			return (false);
		ft_add_redir_node(cmd, redir);
		if (ft_get_cmd_file(token, redir, cmd))
			return (false);
		return (true);
	}
	return (false);
}

t_cmd	*ft_alloc(t_token *token, t_cmd *cmd, t_gc *gc)
{	
	cmd = ft_alloc_and_init_cmd(token, gc);
	if (!cmd)
		return (NULL);
	cmd->token = token;
	return (cmd);
}

t_token	*ft_token_next(t_token *tkn)
{
	if (tkn && tkn->next)
		return (tkn->next->next);
	return (NULL);
}

t_cmd	*ft_pars_extracted_command_list(t_token *tkn, t_gc *gc)
{
	t_cmd	*cmd;
	int		j;

	j = 0;
	cmd = ft_alloc_and_init_cmd(tkn, gc);
	if (!cmd)
		return (NULL);
	cmd->token = tkn;
	while (tkn && tkn->type != PIPE && tkn->type != AND && tkn->type != OPTION)
	{
		if (ft_pars_is_or(tkn))
		{
			if (!ft_valid_redir_process(tkn, cmd, gc))
				return (NULL);
			if (tkn->next != NULL)
				tkn = ft_token_next(tkn);
		}
		else
		{
			cmd->args[j++] = ft_gc_strdup(gc, tkn->value);
			tkn = tkn->next;
		}
	}
	cmd->args[j] = NULL;
	return (cmd);
}
