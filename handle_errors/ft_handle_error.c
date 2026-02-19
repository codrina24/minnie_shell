/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:34:41 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 19:42:29 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/pars_minishell.h"

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_check_lex_and_handle_if_error(char *input, t_gc *gc)
{
	if (!input || !gc)
		return (1);
	if ((ft_check_if_unclosed_quotes(input) != 0)
		|| (ft_simple_syntaxe_call(input) == 1)
		|| (ft_syntaxe_call(input) == 1))
	{
		if (gc && gc->head)
			ft_gc_free_all(gc);
		gc->last_status = 2;
		return (gc->last_status);
	}		
	return (0);
}

int	ft_free_and_update_status_if_error(t_gc *gc, int error_code)
{
	if (!gc)
		return (0);
	if (gc && gc->head)
		ft_gc_free_all(gc);
	gc->last_status = error_code;
	return (gc->last_status);
}
