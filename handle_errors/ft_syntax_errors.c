/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:35:10 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 19:44:16 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

void	ft_get_syntax_error_message(int error)
{
	if (error == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `nl'\n", 2);
	else if (error == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (error == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (error == 4)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (error == 5)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (error == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<<'\n", 2);
	else if (error == 7)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

char	*ft_get_last_in_str(char *str)
{
	static char	new[100];
	int			i;
	int			start;
	int			end;

	i = ft_strlen(str);
	while (i > 0 && str[i - 1] == ' ')
		i--;
	end = i;
	while (i > 0 && str[i - 1] != ' ' && str[i - 1] != '|'
		&& str[i - 1] != '<' && str[i - 1] != '>')
		i--;
	start = i;
	if (start > 0 && (str[start - 1] == '|'
			|| str[start - 1] == '<' || str[start - 1] == '>'))
		start--;
	ft_strlcpy(new, str + start, end - start + 1);
	return (new);
}

char	*ft_strnstr_q(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	lenlittle;

	j = 0;
	lenlittle = ft_strlen(little);
	if (lenlittle == 0)
		return ((char *)big);
	while (big[j] && j + lenlittle <= len)
	{	
		if (!ft_is_in_quotes(big, j))
		{
			if (big[j] == little[0])
			{
				if (ft_strncmp(big + j, little, lenlittle) == 0)
					return ((char *)(big + j));
			}
		}
		j++;
	}
	return (NULL);
}

int	ft_simple_syntaxe_call(char *str)
{
	char	*last_or;
	int		len;

	len = ft_strlen(str);
	last_or = ft_get_last_in_str(str);
	if (ft_strnstr_q(str, "> >", len))
		return (ft_get_syntax_error_message(2), 1);
	else if (ft_strnstr_q(str, "< <", len))
		return (ft_get_syntax_error_message(4), 1);
	else if (ft_strnstr_q(str, "<< <<", len))
		return (ft_get_syntax_error_message(5), 1);
	else if (ft_strnstr_q(str, ">> >>", len))
		return (ft_get_syntax_error_message(5), 1);
	else if (ft_strcmp(last_or, "<<<") == 0)
		return (ft_get_syntax_error_message(1), 1);
	else if ((ft_strcmp(last_or, ">") == 0) || (ft_strcmp(last_or, "<") == 0)
		|| (ft_strcmp(last_or, ">>") == 0) || (ft_strcmp(last_or, "<<") == 0))
		return (ft_get_syntax_error_message(1), 1);
	else if (ft_strcmp(last_or, "|") == 0)
		return (ft_get_syntax_error_message(7), 1);
	return (0);
}

int	ft_syntaxe_call(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{	
		if (str[0] == '|')
			return (ft_get_syntax_error_message(7), 1);
		if (!ft_is_in_quotes(str, i))
		{
			if (ft_strnstr_q(str, "<<<<<<", len))
				return (ft_get_syntax_error_message(6), 1);
			else if (ft_strnstr_q(str, "<<<<<", len))
				return (ft_get_syntax_error_message(5), 1);
			else if (ft_strnstr_q(str, "<<<<", len))
				return (ft_get_syntax_error_message(4), 1);
			else if (ft_strnstr_q(str, ">>>>", len))
				return (ft_get_syntax_error_message(3), 1);
			else if (ft_strnstr_q(str, ">>>", len))
				return (ft_get_syntax_error_message(2), 1);
		}
		i++;
	}
	return (0);
}
