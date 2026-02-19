/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_struct_init_00.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:30:41 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:52:59 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars_minishell.h"

t_cmd	*ft_alloc_and_init_cmd(t_token *token, t_gc *gc)
{
	t_cmd	*cmd;
	int		len;

	len = ft_pars_find_len_without_or_list(token);
	cmd = ft_gc_malloc(gc, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_gc_malloc(gc, sizeof(char *) * (len + 1));
	if (!cmd->args)
		return (NULL);
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->write_fd = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->delim = NULL;
	cmd->exec_fail = 0;
	cmd->redir = NULL;
	cmd->token = NULL;
	return (cmd);
}

t_redir	*ft_new_or(int type, char *file, t_gc *gc)
{
	t_redir	*redir;

	redir = ft_gc_malloc(gc, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_gc_strdup(gc, file);
	if (!redir->file)
	{
		ft_gc_free_one(gc, redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	ft_add_redir_node(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*temp;

	if (!cmd || !new_redir)
		return ;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		temp = cmd->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

t_env	*ft_env_init(t_gc *gc)
{
	t_env	*env;

	if (!gc)
		return (NULL);
	env = ft_gc_malloc(gc, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->eq = NULL;
	env->expp = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

t_env	*ft_env_add_back(t_env *head, t_env *new_env)
{
	t_env	*temp;

	if (!head)
		return (new_env);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
	return (head);
}
