/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spaces_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:26:25 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:09:33 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_is_or(const char *input)
{
	if (!input || !input[0])
	{
		return (INVALID);
	}
	if (input[0] == '&' && (input[1] && input[1] == '&'))
		return (AND);
	if (input[0] == '|' && (input[1] && input[1] == '|'))
		return (OPTION);
	if (input[0] == '>' && (input[1] && input[1] == '>'))
		return (APPEND);
	if (input[0] == '<' && (input[1] && input[1] == '<'))
		return (HEREDOC);
	if (input[0] == '>')
		return (REDOUT);
	if (input[0] == '<')
	{
		return (REDIN);
	}
	if (input[0] == '|')
		return (PIPE);
	return (WORD);
}

int	ft_count_spaces(const char *input, int token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (!ft_is_in_quotes(input, i))
		{
			token = ft_is_or(&input[i]);
			if (token > 0)
			{
				if (token == APPEND || token == HEREDOC
					|| token == AND || token == OPTION)
					count -= 2;
				if (input[i + 1] == '\0')
					count += 1;
				else
					count += 2;
			}
		}
		i++;
	}
	return (count);
}

char	*ft_count_total_size_and_alloc(const char *input, t_gc *gc)
{
	int		len;
	int		spaces;
	int		result;
	int		token;
	char	*expanded;

	token = 0;
	if (!input)
		return (NULL);
	len = ft_strlen(input);
	spaces = ft_count_spaces(input, token);
	if (spaces < 0)
		return (NULL);
	result = len + spaces;
	expanded = ft_gc_malloc(gc, sizeof(char) * (result + 1));
	if (!expanded)
	{
		return (NULL);
	}
	return (expanded);
}

void	ft_add_spaces(const char *input, char *expanded, int *i, int *j)
{
	int	token;

	token = ft_is_or(&input[*i]);
	if (token == APPEND || token == HEREDOC || token == AND || token == OPTION)
	{
		expanded[(*j)++] = ' ';
		expanded[(*j)++] = input[(*i)++];
		expanded[(*j)++] = input[(*i)++];
		if (input[*i] != '\0')
		{
			expanded[(*j)++] = ' ';
		}
		return ;
	}
	else if (token == REDOUT || token == REDIN || token == PIPE)
	{
		expanded[(*j)++] = ' ';
		expanded[(*j)++] = input[(*i)++];
		if (input[*i] != '\0')
		{
			expanded[(*j)++] = ' ';
		}
		return ;
	}
}

char	*ft_expanded_with_spaces(const char *input, t_gc *gc)
{
	char	*expanded;
	int		i;
	int		j;
	int		token;

	i = 0;
	j = 0;
	if (!input || !input[i] || !gc)
		return (NULL);
	expanded = ft_count_total_size_and_alloc(input, gc);
	if (!expanded)
		return (NULL);
	while (input[i])
	{
		token = ft_is_or(&input[i]);
		if (!ft_is_in_quotes(input, i) && (token > WORD))
			ft_add_spaces(input, expanded, &i, &j);
		else
			expanded[j++] = input[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
