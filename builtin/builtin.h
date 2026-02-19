/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:37:11 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 15:58:03 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_env	t_env;
typedef struct s_gc		t_gc;
typedef struct s_cmd	t_cmd;

//**FT_CD

char	*ft_get_path_value(t_env *env, char *str, t_gc *gc);
t_env	*ft_create_env_node(char *search, char *new_value, t_gc *gc);
int		ft_search_and_update(t_env *env, char *search,
			char *new_value, t_gc *gc);
int		ft_up_val(t_env *env, char *search, char *new_value, t_gc *gc);
int		ft_up_pwd(t_env *env, char *oldcwd, char *new_path, t_gc *gc);
char	*ft_get_home(t_cmd *cmd, t_gc *gc, t_env *env);
char	*ft_get_right_path(t_cmd *cmd, t_env *env, t_gc *gc);
char	*ft_implement_dash(t_env *env, t_gc *gc);
int		ft_change_dir(char *path);
int		ft_cd_execute(t_cmd *cmd, t_gc *gc, t_env *env);

int		ft_cd(t_cmd *cmd, t_gc *gc, t_env *env);

//**FT_ECHO

int		ft_search_n(char *arg);
int		ft_n_options(t_cmd *cmd);
void	ft_print_without_option(t_cmd *cmd);
void	ft_print_with_option(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);

//**FT_ENV

int		ft_isuppernum(int c);
void	ft_increment_shlvl(t_gc *gc, t_env *env);
char	*ft_extract_key(t_gc *gc, const char *input);
t_env	*ft_create_env_struct(char *input, t_gc *gc);
t_env	*ft_create_env_list(char **envp, t_env *env, t_gc *gc);
int		ft_env(t_env *env);
int		ft_count_env_lines(t_env *env);
char	*ft_build_env_line(t_env *env, t_gc *gc);
char	**ft_alloc_env_tab(t_env *env, t_gc *gc);
char	**ft_env_tab(t_env *env, t_gc *gc);
int		ft_env(t_env *env);

//**FT_EXIT

int		ft_whitespace_and_sign(char *str, int *signe);
int		ft_number_process(char *str, int i, int signe, long long *result);
int		ft_verify_and_convert_num(char *str, t_cmd *cmd,
			t_gc *gc, t_gc *gc_env);
int		ft_exit(t_cmd *cmd, t_gc *gc, t_gc *gc_env);

//**EXPORT

t_env	*ft_init_env_copy(t_gc *gc);
int		ft_copy_from_env(t_gc *gc, t_env *copy, t_env *env);
t_env	*ft_copy_env(t_gc *gc, t_env *env);
int		ft_print_export(t_gc *gc, t_env *env);
int		ft_process_export_arg(char *arg, t_env *env, t_gc *gc);
t_env	*ft_create_exp_node(char *search, char *new_value, t_gc *gc);
void	ft_up_export(t_env *env, char *search, char *new_value, t_gc *gc);
char	*ft_get_export_value(t_gc *gc, char *str);
char	*ft_is_eq(t_gc *gc, const char *input);
char	*ft_extract_keyy(t_gc *gc, const char *input);
void	ft_swap_key(t_env *env);
void	ft_swap_value(t_env *env);
void	ft_bubble_sort(t_env *env);
void	ft_clean_value(t_env *env, t_gc *gc);
int		ft_export(t_cmd *cmd, t_env *env, t_gc *gc);

//**FT_PWD

int		ft_pwd(void);

//**FT_UNSET

void	ft_remove_from_env(t_env *env, t_gc *gc, char *key_to_remove);
int		ft_unset(t_env *env, t_cmd *cmd, t_gc *gc);
int		ft_supp_protect(const char *path);

#endif
