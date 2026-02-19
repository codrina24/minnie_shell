/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_clean_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:35:58 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/27 18:12:49 by mzerad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../parser/pars_minishell.h"

void	ft_keep_or_strip_quotes_in_token(char *str, int i, int j)
{
	if (!str || i >= (int)ft_strlen(str) || j >= (int)ft_strlen(str))
		return ;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				str[j++] = str[i++];
			if (str[i] == '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				str[j++] = str[i++];
			if (str[i] == '\'')
				i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

t_token	*ft_lex_create_token(const char *value, t_gc *gc)
{
	t_token	*token;

	token = ft_gc_malloc(gc, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_gc_strdup(gc, value);
	if (!token->value)
	{
		return (ft_gc_free_one(gc, token), (NULL));
	}
	ft_keep_or_strip_quotes_in_token(token->value, 0, 0);
	token->type = ft_is_or((char *)value);
	token->next = NULL;
	return (token);
}

t_token	*ft_lex_get_tokens_from_split(char **str, t_gc *gc)
{
	t_token	*head;
	t_token	*last;
	t_token	*node;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	if (!str || !str[i] || !gc)
		return (NULL);
	while (str[i])
	{
		node = ft_lex_create_token(str[i], gc);
		if (!node)
			return (ft_gc_free_one(gc, head), NULL);
		if (!head)
			head = node;
		else
			last->next = node;
		last = node;
		i++;
	}
	return (head);
}
