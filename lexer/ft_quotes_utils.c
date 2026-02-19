/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:37:17 by mzerad            #+#    #+#             */
/*   Updated: 2026/02/19 17:28:55 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

int	ft_check_if_unclosed_quotes(const char *str)
{
	char	quote;
	int		i;

	quote = '\0';
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
		{
			if (quote == '\0')
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
		}
		i++;
	}
	if (quote != '\0')
	{
		ft_putstr_fd("minishell: missing or invalid quote >\n", 2);
		return (1);
	}
	return (0);
}

int	ft_count_double_quotes(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		if (str[i] == '\'')
			break ;
		i++;
	}
	return (count);
}

bool	ft_is_in_single_quotes(const char *str, int pos)
{
	int			i;
	int			count_dub;
	bool		in_single_quote;

	i = 0;
	in_single_quote = false;
	count_dub = ft_count_double_quotes(str);
	if (!str || pos < 0)
		return (false);
	while (i < pos && str[i])
	{
		if (str[i] == '"' && (count_dub % 2 != 0))
			return (in_single_quote);
		else if (str[i] == '\'')
		{
			in_single_quote = !in_single_quote;
		}		
		i++;
	}
	return (in_single_quote);
}

bool	ft_is_in_double_quotes(const char *str, int pos)
{
	int		i;
	bool	in_double_quotes;

	i = 0;
	in_double_quotes = false;
	if (!str || pos < 0)
		return (false);
	while (i < pos && str[i])
	{
		if (str[i] == '"')
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (in_double_quotes);
}

bool	ft_is_in_quotes(const char *str, int pos)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (!str || pos < 0)
		return (false);
	while (i < pos && str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
}
