/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:06:03 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/28 13:24:16 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_redir	t_redir;
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_gc		t_gc;
typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;
typedef int				(*t_exec_point) (
								t_ast	*ast,
								t_gc	*gc,
								t_gc	*gc_env
							);
typedef struct s_exec
{
	int				type;
	t_exec_point	callback;
}				t_exec;

//					EXEC

//**FT_EXEC_BUILD_PATH_AND_UTILS

char	*ft_get_path_value_(t_env *env, t_gc *gc);
char	**ft_split_path_value(t_env *env, t_gc *gc);
char	*ft_build_complete_path_process(t_env *env, char *command, t_gc *gc);
int		ft_input_is_empty_or_whitespace(const char *str);
t_gc	*ft_static_ptr(t_gc *init);

//**FT_EXEC_BUILTIN

int		ft_cd(t_cmd *cmd, t_gc *gc, t_env *env);
int		ft_special_case_env(char *first, t_env *env, t_cmd *cmd);
int		ft_verify_first_argument(t_cmd *cmd);
int		ft_exec_builtin(t_cmd *cmd, t_env *env, t_gc *gc);

//**FT_EXEC_MAIN_PREPARE

int		ft_check_tty(void);
char	*ft_wondering(char *input);
char	*ft_copy_input(void);
int		ft_handle_input(char *input, t_gc *gc);
int		ft_mini_world(t_env *env, t_ast **ast, t_gc *gc, t_gc *gc_env);

//**FT_EXEC_PIPES_00

int		ft_count_pipes_ast(t_ast *ast);
void	ft_share_with(t_ast *ast, pid_t *pids, int *pid_count, int pid_size);
void	ft_prepare_shared_package(t_ast *ast, t_gc *gc);
void	ft_waitpid(pid_t pid, int *status);
int		ft_wait_for_children(t_ast *ast, int pid_count, t_gc *gc);

//**FT_EXEC_PIPES_01

void	ft_create_pipe(int *fd);
void	ft_clean_resources(t_gc *gc, t_gc *gc_env);
void	ft_close_fd(int input_fd, t_ast *ast);
void	ft_add_pid(t_ast *ast, pid_t pid);

//**FT_EXEC_PIPES_02

void	ft_prepre_exec(t_ast *ast, t_gc *gc, t_gc *gc_env);
void	ft_pipe_node(t_ast *ast);
void	ft_child_pipe(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env);
void	ft_parent_pipe(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env);
void	ft_exec_pipes(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env);

//**FT_EXEC_SIMPLE_EXTERN_COMMANDS

void	ft_dup_it_v2(int fd_source, int fd_result);
void	ft_setup(t_ast *ast, int input_fd);
void	ft_child_simple(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env);
void	ft_parent_simple(int input_fd, pid_t pid, t_gc *gc);
void	ft_process_simple(t_ast *ast, int input_fd, t_gc *gc, t_gc *gc_env);

//**FT_EXECVE 

void	ft_check_execve_args_or_exit(t_gc *gc, t_gc *gc_env, t_cmd *cmd);
char	**ft_get_env_or_exit(t_env *envp, t_gc *gc, t_gc *gc_env);
void	ft_execve_direct_path(t_gc *gc, t_gc *gc_env, t_cmd *cmd, char **env);
void	ft_execve(t_cmd *cmd, t_env *envp, t_gc *gc, t_gc *gc_env);
int		ft_choose_redir(t_cmd *cmd, t_redir *redir);

//**FT_HEREDOC_LOOP

char	*ft_expand_in_heredoc(char *line, t_gc *gc, t_gc *gc_env);
void	ft_write_line(char *line, t_cmd *cmd, t_gc *gc, t_gc *gc_env);
int		ft_is_delim(char *line, char *delim, t_gc *gc);
int		ft_heredoc_loop(t_cmd *cmd, t_gc *gc, t_gc *gc_env, bool is_child);
int		ft_heredoc_process(t_cmd *cmd, t_gc *gc, t_gc *gc_env);

//**FT_HEREDOC_PIPE

void	ft_heredoc_child(t_cmd *cmd, int *fd, t_gc *gc, t_gc *gc_env);
int		ft_catch_parent_status(int *fd, int status, t_gc *gc);
int		ft_handle_heredoc_pipe(t_cmd *cmd, t_gc *gc, t_gc *gc_env);
int		ft_handle_heredoc_redir(t_ast *ast, t_redir *redir,
			t_gc *gc, t_gc *gc_env);
int		ft_prep_heredoc(t_ast *ast, t_gc *gc, t_gc *gc_env);

//**FT_HEREDOC_SIMPLE

int		ft_line_and_status_check(char *line,
			int write_fd, char *delim, t_gc *gc);
int		ft_create_temp_file(t_cmd *cmd, t_gc *gc);
void	ft_failed_heredoc_process(t_cmd *cmd);
void	ft_success_heredoc_process(t_cmd *cmd);
int		ft_handle_heredoc(t_cmd *cmd, t_gc *gc, t_gc *gc_env);

//**FT_PRE_EXEC_00

char	**ft_clear_input(t_gc *gc, t_env *env, char *input);
t_cmd	*ft_tokens_and_cmd(char **split, t_gc *gc);
void	ft_eof_in_quotes(char **split, t_gc *gc);
int		ft_pre_exec(t_env *env, char *input, t_ast **ast, t_gc *gc);
int		ft_exec_builtin_cmd(t_ast *ast, t_gc *gc, t_gc *gc_env);

//**FT_PRE_EXEC_01

int		ft_exec_cmd_node(t_ast *ast, t_gc *gc, t_gc *gc_env);
int		ft_exec_pipe_node(t_ast *ast, t_gc *gc, t_gc *gc_env);
int		ft_exec_and_node(t_ast *ast, t_gc *gc, t_gc *gc_env);
int		ft_exec_option_node(t_ast *ast, t_gc *gc, t_gc *gc_env);
int		ft_exec(t_ast *ast, t_gc *gc, t_gc *gc_env);

//**FT_REDIR_BUILTIN

int		ft_lets_dup(int *original_stdout, int *original_stdin);
int		ft_dup2_in_builtin(t_cmd *cmd);
void	ft_restore_fds(int original_stdout, int original_stdin);
void	ft_centralize_errors(char x, int original_stdout, int original_stdin);
int		ft_exec_builtin_with_redir(t_cmd *cmd, t_env *env,
			t_gc *gc, t_gc *gc_env);

//**FT_REDIR

int		ft_file_in(t_cmd *cmd, char *file);
int		ft_file_out(t_cmd *cmd, char *file);
int		ft_file_out_append(t_cmd *cmd, char *file);
int		ft_file_in_heredoc(t_cmd *cmd, char *file);
int		ft_open_redir(t_cmd *cmd);

//				SIGNALS

//**FT_HANDLE_SIGNALS_00

int		ft_handle_error_signal(t_gc *gc);
void	ft_sigint_handler(int signum);
void	ft_update_last_status(int status, t_gc *gc);

//**FT_HANDLE_SIGNALS_01

void	ft_setup_signals(void);
void	ft_reset_signals_to_default(void);
void	ft_ign_signals(void);

//**FT_HANDLE_HEREDOC_SIGNALS

int		ft_mark_it(void);
void	ft_heredoc_sigint_handler(int signum);
void	ft_setup_signals_heredoc(void);
void	ft_sigint_close_heredoc(char *line, int write_fd, t_gc *gc);

//				HANDLE_ERRORS

//**FT_EXEC_ERRORS_00

int		ft_check_env_args(t_cmd *cmd);
void	ft_error_exit_value(t_cmd *cmd);
int		ft_another_error(t_cmd *cmd, t_gc *gc, t_gc *gc_env);

//**FT_EXEC_ERRORS_01

int		ft_error_null_env(t_gc *gc, t_gc *gc_env);
void	ft_error_cd(void);
void	ft_error_export(const char *input);
void	ft_error_stat(char *command_path, char **split_values, t_gc *gc);
void	ft_error_heredoc(const char *delim);

//**FT_EXEC_ERRORS_02

int		ft_error_onetwosix(t_cmd *cmd, t_gc *gc, t_gc *gc_env);
int		ft_error_onetwoseven(t_cmd *cmd, t_gc *gc, t_gc *gc_env);
char	*ft_access_errors_built_path(char *command_path,
			char **split_values, t_gc *gc);
void	ft_access_errors_abs_or_relatif(t_cmd *cmd, t_gc *gc, t_gc *gc_env);
void	ft_errors_execve(t_cmd *cmd, char *path, t_gc *gc, t_gc *gc_env);

//				MAIN

//**MAIN

void	ft_start(void);
int		ft_safe_return(t_gc *gc, t_gc *gc_env, int last_status);

#endif
