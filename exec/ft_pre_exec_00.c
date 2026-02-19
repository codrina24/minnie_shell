/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_exec_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:43:14 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 13:38:55 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

char	**ft_clear_input(t_gc *gc, t_env *env, char *input)
{
	char	*new;
	char	*expanded;
	char	**split;

	new = ft_expand_token(gc, env, input);
	if (!new)
		return (NULL);
	expanded = ft_expanded_with_spaces(new, gc);
	if (!expanded)
		return (ft_gc_free_one(gc, new), NULL);
	split = ft_lex_split(expanded, ' ', gc);
	if (!split)
		return (ft_gc_free_one(gc, new), ft_gc_free_one(gc, expanded), NULL);
	return (split);
}

t_cmd	*ft_tokens_and_cmd(char **split, t_gc *gc)
{
	t_token	*tokens;
	t_token	*tmp;
	t_cmd	*cmd;

	tokens = ft_lex_get_tokens_from_split(split, gc);
	tmp = tokens;
	while (tmp)
	{
		tmp = tmp->next;
	}
	cmd = ft_pars_extracted_command_list(tokens, gc);
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	ft_eof_in_quotes(char **split, t_gc *gc)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strcmp(split[i], "<<") == 0)
		{
			gc->in_quotes_eof = 0;
			if (split[i + 1])
			{
				if (ft_is_in_quotes(split[i + 1], i))
				{
					gc->in_quotes_eof = 2;
				}
			}
		}
		i++;
	}
}

int	ft_pre_exec(t_env *env, char *input, t_ast **ast, t_gc *gc)
{
	char	**split_input;
	t_cmd	*cmd;

	split_input = ft_clear_input(gc, env, input);
	if (!split_input)
		return (-1);
	ft_eof_in_quotes(split_input, gc);
	cmd = ft_tokens_and_cmd(split_input, gc);
	if (!cmd)
		return (-1);
	*ast = ft_create_ast(cmd, gc);
	if (!*ast)
		return (-1);
	return (0);
}

int	ft_exec_builtin_cmd(t_ast *ast, t_gc *gc, t_gc *gc_env)
{
	int	status;

	if (ft_strcmp(ast->cmd->args[0], "exit") == 0)
	{
		gc->last_status = ft_exit(ast->cmd, gc, gc_env);
		return (gc->last_status);
	}
	if (ast->cmd->redir && ast->cmd->redir->type == HEREDOC)
		ft_handle_heredoc(ast->cmd, gc, gc_env);
	if (ast->cmd->input_fd != -1 || ast->cmd->output_fd != -1)
		status = ft_exec_builtin_with_redir(ast->cmd, gc_env->env, gc, gc_env);
	else
		status = ft_exec_builtin(ast->cmd, gc_env->env, gc_env);
	gc->last_status = status;
	return (gc->last_status);
}
