/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_minishell.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:02:20 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/27 18:16:54 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_MINISHELL_H
# define PARS_MINISHELL_H

# include "../gc/gc.h"
# include "../libft/libft.h"
# include "../builtin/builtin.h"
# include "../exec/exec.h"
# include "../expand/expand.h"
# include <errno.h>
# include <limits.h> 
# include <time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <sys/stat.h>
# include <sys/sysmacros.h>
# include <time.h>
# include <signal.h>

extern volatile sig_atomic_t	g_signal_received;

# define IS_BUILTIN 0
# define NOT_BUILTIN 1
# define COMMAND_NODE 24
# define PIPE_NODE 42
# define  AND_NODE 111
# define  OPTION_NODE 22

typedef struct s_env
{
	char			*key;
	char			*eq;
	char			*expp;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef enum type
{
	INVALID = -1,
	WORD = 0,
	PIPE,
	REDIN,
	REDOUT,
	HEREDOC,
	APPEND,
	AND,
	OPTION,
	END
}		t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}			t_redir;

typedef struct s_cmd
{
	char	**args;
	int		fd_count;
	char	*temp_fd;
	int		input_fd;
	int		output_fd;
	int		write_fd;
	char	*input_file;
	char	*output_file;
	char	*delim;
	int		exec_fail;
	t_token	*token;
	t_redir	*redir;
	t_env	*env;
}				t_cmd;

typedef struct s_ast
{
	t_cmd			*cmd;
	int				type;
	int				fd[2];
	int				exec_fail;
	int				nbr_cmd;
	pid_t			*pids;
	int				*pid_count;
	int				pid_size;
	int				is_pipe;
	struct s_ast	*first_child;
	struct s_ast	*second_child;
}						t_ast;

typedef struct s_gc				t_gc;

//                   LEXER                      //

//**FT_GET_CLEAN_TOKEN

void		ft_keep_or_strip_quotes_in_token(char *str, int i, int j);
t_token		*ft_lex_create_token(const char *value, t_gc *gc);
t_token		*ft_lex_get_tokens_from_split(char **str, t_gc *gc);

//**FT_LEX_SPLIT

int			ft_count_segments(const char *s, char c);
int			ft_split_process(const char *s, char c, int *i);
int			ft_lex_split_process(char **tab, char *s, char c, t_gc *gc);
char		**ft_lex_split(char *s, char c, t_gc *gc);

//**FT_QUOTES_UTILS

int			ft_check_if_unclosed_quotes(const char *str);
int			ft_count_double_quotes(const char *str);
bool		ft_is_in_single_quotes(const char *str, int pos);
bool		ft_is_in_double_quotes(const char *str, int pos);
bool		ft_is_in_quotes(const char *str, int pos);

//                   HANDLE_ERRORS                     //

//**FT_HANDLE_ERROR

bool		ft_isspace(char c);
int			ft_check_lex_and_handle_if_error(char *input, t_gc *gc);
int			ft_free_and_update_status_if_error(t_gc *gc, int error_code);

//**FT_SYNTAX_ERROR

void		ft_get_syntax_error_message(int error);
char		*ft_get_last_in_str(char *str);
char		*ft_strnstr_q(const char *big, const char *little, size_t len);
int			ft_simple_syntaxe_call(char *str);
int			ft_syntaxe_call(char *str);

//**FT_PARS_STRUCT_INIT_00

t_cmd		*ft_alloc_and_init_cmd(t_token *token, t_gc *gc);
t_redir		*ft_new_or(int type, char *file, t_gc *gc);
void		ft_add_redir_node(t_cmd *cmd, t_redir *new_redir);
t_env		*ft_env_init(t_gc *gc);
t_env		*ft_env_add_back(t_env *head, t_env *new_env);

//**FT_PARS_STRUCT_INIT_01

t_ast		*ft_pars_new_command_node(t_cmd *cmd, t_gc *gc);
t_ast		*ft_new_ast_node(t_ast *first, t_ast *second,
				int magic_nbr, t_gc *gc);
int			ft_pars_find_len_without_or_list(t_token *token);

//**FT_PARSE_COMMAND

int			ft_pars_find_len_without_or_list(t_token *token);
int			ft_get_cmd_file(t_token *token, t_redir *redir, t_cmd *cmd);
bool		ft_valid_redir_process(t_token *token, t_cmd *cmd, t_gc *gc);
t_token		*ft_token_next(t_token *tkn);
t_cmd		*ft_pars_extracted_command_list(t_token *token, t_gc *gc);

//**FT_PARS_AST

t_token		*ft_find_this_token(t_token *token, int magic_nbr);
t_ast		*ft_create_first_node(t_cmd *cmd, t_gc *gc);
t_ast		*ft_create_team(t_token *next_tokens, t_ast *first,
				int magic_nbr, t_gc *gc);
t_ast		*ft_create_ast(t_cmd *cmd, t_gc *gc);

#endif
