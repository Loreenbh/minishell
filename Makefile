NAME        = minishell
FT_ECHO		= ft_echo

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -MMD -g3

INC_LIBFT   = ./libft/includes
INC_SRCS    = ./srcs/incs
INC         = -I$(INC_LIBFT) -I$(INC_SRCS)

#================SRC================

#=== DIR ====
SRC_DIR     		= srcs/
BUILT_DIR   		= $(SRC_DIR)builtins/
UTILS_DIR   		= $(SRC_DIR)utils/
EXEC_DIR			= $(SRC_DIR)exec/
UTILS_FREE_DIR 		= $(UTILS_DIR)free/
UTILS_PRINT_DIR 	= $(UTILS_DIR)print/
UTILS_DUP_DIR 		= $(UTILS_DIR)dup/
UTILS_CREATE_DIR 	= $(UTILS_DIR)create/
UTILS_SYNTAX_DIR 	= $(UTILS_DIR)syntax/
PARSING_DIR 		= $(SRC_DIR)parsing/
PARSING_TOKEN_DIR 	= $(PARSING_DIR)tokens/
FT_ECHO_DIR			= $(BUILT_DIR)ft_echo/

#=== FILE ===
SRC					= main.c
BUILT_SRC			= ft_cd.c ft_export.c ft_pwd.c ft_unset.c ft_exit.c
EXEC_SRC			= heredoc_utils2.c exec_cd2.c search_path_built.c exec_unset.c exec_export.c one_child.c start_exec.c init_cmd.c cmd_utils.c exec_all_cmd.c exec_cmd.c exec_one_cmd.c exec_utils.c heredoc_utils.c gen_env.c parent_task.c exec_cd.c get_path.c exec_other_bltn.c
UTILS_SRC			= ft_getenv.c signal.c
UTILS_FREE_SRC		= free_minish.c free_check.c free_dt_elem.c free_cmd.c
UTILS_PRINT_SRC		= print_dt_elem.c print_cmd.c print_env.c
UTILS_CREATE_SRC	= create_check.c create_minish.c create_dt_elem.c create_cmd.c
UTILS_SYNTAX_SRC	= syntax.c type.c
PARSING_SRC			= parsing.c parsing_syntax.c parsing_operator.c parsing_element.c parsing_quote.c parsing_last_verif.c
PARSING_TOKEN_SRC	= tokens_quote.c tokens_redir.c tokens_other.c tokens_whitespace.c parse_normal.c
FT_ECHO_SRC			= ft_echo.c

#================OBJ================

OBJ_DIR					= objs/

OBJ         			= $(SRC:.c=.o)
OBJ_DIR_SRC 			= $(addprefix $(OBJ_DIR), $(OBJ))

OBJ_BUILD   			= $(BUILT_SRC:.c=.o)
OBJ_DIR_BUILD 			= $(addprefix $(OBJ_DIR), $(OBJ_BUILD))

OBJ_EXEC   				= $(EXEC_SRC:.c=.o)
OBJ_DIR_EXEC 			= $(addprefix $(OBJ_DIR), $(OBJ_EXEC))

OBJ_UTILS_FREE   		= $(UTILS_FREE_SRC:.c=.o)
OBJ_DIR_UTILS_FREE		= $(addprefix $(OBJ_DIR), $(OBJ_UTILS_FREE))

OBJ_UTILS   			= $(UTILS_SRC:.c=.o)
OBJ_DIR_UTILS 			= $(addprefix $(OBJ_DIR), $(OBJ_UTILS))

OBJ_UTILS_PRINT   		= $(UTILS_PRINT_SRC:.c=.o)
OBJ_DIR_UTILS_PRINT 	= $(addprefix $(OBJ_DIR), $(OBJ_UTILS_PRINT))

OBJ_UTILS_CREATE   		= $(UTILS_CREATE_SRC:.c=.o)
OBJ_DIR_UTILS_CREATE	= $(addprefix $(OBJ_DIR), $(OBJ_UTILS_CREATE))

OBJ_UTILS_SYNTAX   		= $(UTILS_SYNTAX_SRC:.c=.o)
OBJ_DIR_UTILS_SYNTAX 	= $(addprefix $(OBJ_DIR), $(OBJ_UTILS_SYNTAX))

OBJ_PARSING				= $(PARSING_SRC:.c=.o)
OBJ_DIR_PARSING			= $(addprefix $(OBJ_DIR), $(OBJ_PARSING))

OBJ_PARSING_TOKEN 		= $(PARSING_TOKEN_SRC:.c=.o)
OBJ_DIR_PARSING_TOKEN 	= $(addprefix $(OBJ_DIR), $(OBJ_PARSING_TOKEN))

LIBFTDIR    			= lib
LIBFT       			= $(LIBFTDIR)/libft.a

OBJ_FT_ECHO 			= $(FT_ECHO_SRC:.c=.o)
OBJ_DIR_FT_ECHO 		= $(addprefix $(OBJ_DIR), $(OBJ_FT_ECHO))

#================RULES================

all: ${NAME}
	@clear
	@echo "./minishell a été créé. 💯\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(BUILT_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_PRINT_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_FREE_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_CREATE_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_SYNTAX_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(UTILS_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c
	echo fjfiwjfw
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_TOKEN_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(FT_ECHO_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

-include $(OBJ_DIR_SRC:.o=.d)
-include $(OBJ_DIR_BUILD:.o=.d)
-include $(OBJ_DIR_EXEC:.o=.d)
-include $(OBJ_DIR_UTILS:.o=.d)
-include $(OBJ_DIR_UTILS_FREE:.o=.d)
-include $(OBJ_DIR_UTILS_PRINT:.o=.d)
-include $(OBJ_DIR_UTILS_CREATE:.o=.d)
-include $(OBJ_DIR_UTILS_SYNTAX:.o=.d)
-include $(OBJ_DIR_PARSING:.o=.d)
-include $(OBJ_DIR_PARSING_TOKEN:.o=.d)
-include $(OBJ_DIR_FT_ECHO:.o=.d)

${NAME}: $(LIBFT) $(FT_ECHO) $(OBJ_DIR_SRC) $(OBJ_DIR_EXEC) $(OBJ_DIR_PARSING) $(OBJ_DIR_UTILS_SYNTAX) $(OBJ_DIR_UTILS_PRINT) $(OBJ_DIR_PARSING_TOKEN) $(OBJ_DIR_BUILD) $(OBJ_DIR_UTILS) $(OBJ_DIR_UTILS_FREE) $(OBJ_DIR_UTILS_CREATE)
	$(CC) $(CFLAGS) $(OBJ_DIR_SRC) $(OBJ_DIR_EXEC) $(OBJ_DIR_PARSING) $(OBJ_DIR_UTILS_SYNTAX) $(OBJ_DIR_UTILS_PRINT) $(OBJ_DIR_PARSING_TOKEN) $(OBJ_DIR_BUILD) $(OBJ_DIR_UTILS) $(OBJ_DIR_UTILS_FREE) $(OBJ_DIR_UTILS_CREATE) $(LIBFT) -o $@ $(INC) -lreadline

$(LIBFT):
	@make -C libft

$(FT_ECHO): $(LIBFT) $(OBJ_DIR_FT_ECHO)
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR_FT_ECHO) $(INC)

clean:
	@rm -rf ${OBJ_DIR}
	@make -C libft clean > /dev/null 2>&1
	@echo "\nObjets : 🗑️\n"

fclean: clean
	@rm -rf $(FT_ECHO)
	@rm -rf ${NAME}
	@make -C libft fclean > /dev/null 2>&1
	@echo "./minishell et les objets : 🗑️\n"

re: fclean all

run: $(NAME)
	@clear
	@./minishell

run_env_i: $(NAME)
	@clear
	@env -i ./minishell

run_env_i_v: $(NAME)
	@clear
	@env -i valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes --suppressions=/home/glions/minishell2/trash.supp ./minishell

run_v: $(NAME)
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes --track-fds=yes --suppressions=/home/glions/minishell2/trash.supp ./minishell

push: fclean
	@git add .
	@git commit -m "VOIR README"
	@git push

.PHONY: all clean fclean re