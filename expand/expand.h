/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:12:54 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 16:07:06 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_env	t_env;
typedef struct s_gc		t_gc;
typedef struct s_token	t_token;

//** FT_SPACES_EXPAND 

int		ft_is_or(const char *input);
int		ft_count_spaces(const char *input, int token);
char	*ft_count_total_size_and_alloc(const char *input, t_gc *gc);
void	ft_add_spaces(const char *input, char *exp, int *i, int *j);
char	*ft_expanded_with_spaces(const char *input, t_gc *gc);

//** FT_UTILS_EXPAND

bool	ft_pars_is_or(t_token *token);
char	*ft_get_env_value(t_env *env, const char *key);
int		ft_expand_exit_status(t_gc *gc, int i);
int		ft_missing_env_val(char *env_val, char *var_name, t_gc *gc);

//** FT_VAR_EXPAND

int		ft_expand_env_var(t_gc *gc, t_env *env, const char *input, int i);
int		ft_expand_dollar(t_gc *gc, t_env *env, const char *input, int i);
char	*ft_expand_process(t_gc *gc, t_env *env, const char *input);
char	*ft_expand_token(t_gc *gc, t_env *env, const char *input);

#endif