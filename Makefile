NAME		= minishell
INC			= parsing_minishell.h

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

OBJ_DIR     = obj

SRC         = ./signals/ft_handle_heredoc_signals.c\
			  ./signals/ft_handle_signals_00.c\
			  ./signals/ft_handle_signals_01.c\
			  ./gc/gc_free.c\
			  ./gc/gc_init_track_and_malloc.c\
			  ./gc/gc_alloc_functions.c\
			  ./gc/gc_split.c\
			  ./expand/ft_var_expand.c\
			  ./expand/ft_utils_expand.c\
			  ./expand/ft_spaces_expand.c\
			  ./lexer/ft_quotes_utils.c\
			  ./lexer/ft_lex_split.c\
			  ./lexer/ft_get_clean_token.c\
			  ./parser/ft_parse_command.c\
			  ./parser/ft_pars_struct_init_00.c\
			  ./parser/ft_pars_struct_init_01.c\
			  ./parser/ft_pars_ast.c\
			  ./handle_errors/ft_syntax_errors.c\
			  ./handle_errors/ft_handle_error.c\
			  ./handle_errors/ft_exec_errors_00.c\
			  ./handle_errors/ft_exec_errors_01.c\
			  ./handle_errors/ft_exec_errors_02.c\
			  ./builtin/ft_echo.c\
			  ./builtin/ft_cd_00.c\
			  ./builtin/ft_cd_01.c\
			  ./builtin/ft_pwd.c\
			  ./builtin/ft_env_00.c\
			  ./builtin/ft_env_01.c\
			  ./builtin/ft_export_00.c\
			  ./builtin/ft_export_01.c\
			  ./builtin/ft_export_02.c\
			  ./builtin/ft_unset.c\
			  ./builtin/ft_exit.c\
			  ./main.c \
			  ./exec/ft_exec_builtin.c\
			  ./exec/ft_exec_build_path_and_utils.c\
			  ./exec/ft_execve.c\
			  ./exec/ft_exec_main_prepare.c\
			  ./exec/ft_redir.c\
			  ./exec/ft_redir_builtin.c\
			  ./exec/ft_exec_simple_extern_commands.c\
			  ./exec/ft_exec_pipes_00.c\
			  ./exec/ft_exec_pipes_01.c\
			  ./exec/ft_exec_pipes_02.c\
			  ./exec/ft_heredoc_loop.c\
			  ./exec/ft_heredoc_simple.c\
			  ./exec/ft_heredoc_pipe.c\
			  ./exec/ft_pre_exec_00.c\
			  ./exec/ft_pre_exec_01.c\
			   

OBJ = $(patsubst ./%.c,$(OBJ_DIR)/%.o,$(SRC))

CC          = cc
LDFLAGS     = -lreadline
CFLAGS      = -Wall -Werror -Wextra -g3  
RM          = rm -f

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) > /dev/null 

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)
	@echo "\033[1;35m--------------------------\033[0m"
	@echo "\033[1;35m√ Compilation successful √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null

clean:
	@make clean -C $(LIBFT_DIR) > /dev/null 
	@rm -rf $(OBJ_DIR) 
	@echo "\033[1;35m--------------------------\033[0m"
	@echo "\033[1;35m√ Clean done √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) > /dev/null
	@echo "\033[1;35m√ ${NAME} deleted √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

re: fclean all

lib:
	@make -C $(LIBFT_DIR) > /dev/null 

.PHONY: all clean fclean re lib

