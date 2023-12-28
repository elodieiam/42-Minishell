NAME	=	minishell

SRC_DIR	=	src

SRC		=	main.c signals.c data.c \
			lexer/lexer.c lexer/lexer_utils.c lexer/tokens.c lexer/free_lexer.c \
			parsing/parsing.c parsing/tree.c parsing/cmd_node.c parsing/rdlist.c parsing/op_node.c \
			parsing/parenthesis.c \
			exit/exit_line.c \
			exec/exec.c exec/execve.c exec/exec_utils.c exec/exec_env.c exec/heredoc.c \
			exec/heredoc_utils.c exec/redirections.c exec/pipe.c exec/pidlist.c \
			exec/builtins/echo.c exec/builtins/export.c exec/builtins/export_utils.c \
			exec/builtins/export_env.c exec/builtins/exit.c exec/builtins/cd.c \
			exec/builtins/export_append.c exec/builtins/pwd.c exec/builtins/unset.c \
			exec/builtins/builtins.c expand/asterisk.c expand/expand.c expand/expand_utils.c \
			expand/expand_process.c \
			debug.c

OBJ_DIR	=	obj

OBJ		=	$(SRC:%.c=%.o)

OBJS	=	$(addprefix $(OBJ_DIR)/, $(OBJ))

OBJ_COUNT := 0

########	CC  & FLAGS		########

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./include -g3 -fsanitize=address
# CFLAGS	=	-Wall -Wextra -Werror -I./include -g3

RM_FLAGS = -rf

########		LIBFT		########

LFT_DIR	=	libft

LIBFT	=	$(LFT_DIR)/libft.a

########		COLORS		########

COLOR_RESET	=	\033[0m
COLOR_RED	=	\033[1;31m
COLOR_GREEN	=	\033[1;32m
COLOR_YELLOW =	\033[1;93m
COLOR_BLUE =	\033[1;94m
COLOR_PINK	=	\033[38;5;206m
COLOR_LBLUE	=	\033[1;94m

########		RULES		########

all	:			$(NAME)

$(NAME) :		$(OBJS) $(LIBFT) 
				@$(CC) $(CFLAGS) -L$(LFT_DIR) $^ -o $@ -lreadline
				@echo "$(COLOR_GREEN)$(NAME) has been successfully built!$(COLOR_RESET)"
				@clear
				@echo "$(COLOR_LBLUE)"
				@echo "		==================================================================="
				@echo "		███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
				@echo "		████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
				@echo "		██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
				@echo "		██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
				@echo "		██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
				@echo "		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
				@echo "		==================================================================="
				@echo "$(COLOR_RESET)"
				@./minishell

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval OBJ_COUNT=$(shell expr $(OBJ_COUNT) + 1))
	@printf "\033[K\r"
	@printf "[$(COLOR_BLUE)%d%%$(COLOR_RESET)] $(notdir $<)" $$(expr $$(($(OBJ_COUNT) * 100)) / $(words $(SRC)))




$(LIBFT) :
				@echo "\n$(COLOR_YELLOW)Making libft...$(COLOR_RESET)"
				@make -sC $(LFT_DIR)
				@echo "$(COLOR_GREEN)Libft has been built successfully!$(COLOR_RESET)"

clean : 
				@echo "$(COLOR_YELLOW)Cleaning libft...$(COLOR_RESET)"
				@make -sC $(LFT_DIR) clean
				@echo "$(COLOR_RED)Cleaning .o files...$(COLOR_RESET)"
				@rm $(RM_FLAGS) $(OBJS)
				@echo "$(COLOR_GREEN)Project cleaned!$(COLOR_RESET)"

fclean :		clean
				@echo "$(COLOR_YELLOW)Cleaning executable and libft.a...$(COLOR_RESET)"
				@make -sC $(LFT_DIR) fclean
				@rm $(RM_FLAGS) $(NAME)
				@echo "$(COLOR_RED)Project fully cleaned!$(COLOR_RESET)"

re:				fclean all

.PHONY:			all clean fclean re

