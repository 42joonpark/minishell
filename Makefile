# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donpark <donpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 20:09:59 by donpark           #+#    #+#              #
#    Updated: 2021/11/16 19:46:49 by donpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	gcc
CFLAGS		:=	-g -Wall -Wextra -Werror $(CHECK)
CHECK		:=	-fsanitize=address

OS 			:= $(shell uname)
USERS 		:= $(shell Users)
ifeq ($(OS), Linux)
RDLINE_DIR	:=	/usr/share/readline/
RDLINE_INC	:=	/usr/include/readline/
else ifeq ($(USERS), joonpark)
RDLINE_DIR	:=	/Users/joonpark/.brew/opt/readline/lib/
RDLINE_INC	:=	/Users/joonpark/.brew/opt/readline/include/
else ifeq ($(USERS), donpark)
RDLINE_DIR	:=	/Users/donpark/brew/opt/readline/lib/
RDLINE_INC	:=	/Users/donpark/brew/opt/readline/include/
endif

LIBFT_DIR	:=	./libft/
LIBFT_LIB	:=	$(LIBFT_DIR)libft.a
LIBFT_INC	:=	$(LIBFT_DIR)

INC_DIR		:=	./includes/
INCLUDES	:=	minishell.h
INCS		:=	$(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./src/
SOURCES		:=	main.c \
				signal.c \
				clear_screen.c \
				tokenizer.c \
				parse_util.c \
				parse_1.c \
				check_1.c \
				parse_2.c \
				parse_2_1.c \
				parse_3.c \
				parse_3_1.c \
				error.c \
				pipe.c \
				redirect.c \
				cd/cd.c \
				echo/echo.c \
				env/env_list.c \
				env/env.c \
				export/export_add_env.c \
				export/export_add_exp.c \
				export/export_list.c \
				export/export_utils.c \
				export/export.c \
				pwd/pwd.c \
				unset/unset.c \
				utils/pp_lst.c \
				utils/pp_lst_util.c \
				utils/pp_strcmp_limit.c \
				utils/free.c \
				utils/pp_which.c \
				execute.c \
				init.c \
				child_process.c \
				exec.c \
				execute_arg.c \
				parent_process.c \
				test.c
SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))

OBJS_DIR	:=	./obj/
OBJECTS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(LIBFT_DIR) -lft -L$(RDLINE_DIR) -lreadline
HEADERS		:= -I$(INC_DIR) -I$(RDLINE_INC) -I$(LIBFT_INC)

NAME		:=	minishell

# colors
RED			:=	\033[31m
GREEN 		:=	\033[32m
YELLOW 		:=	\033[33m
BLUE 		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
WHITE		:=	\033[37m
PINK		:=	\033[38;5;201m
OBJS_DOT	:=	\033[38;5;201m\033[48;5;252m\033[1m\033[3m
MENT		:=	\033[38;5;191m\033[1m
RE_MENT		:=	\033[38;5;63m\033[1m
RESET		:=	\033[0m

.PHONY		:=	all $(NAME) clean fclean re

$(NAME) : $(LIBFT_LIB) $(OBJS_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBRARY) $(HEADERS)
	@echo "\n$(GREEN)object files were created$(RESET)"
	@echo "$(RED)minishell created.$(RESET)"

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)utils
	@mkdir -p $(OBJS_DIR)pwd
	@mkdir -p $(OBJS_DIR)echo
	@mkdir -p $(OBJS_DIR)cd
	@mkdir -p $(OBJS_DIR)env
	@mkdir -p $(OBJS_DIR)export
	@mkdir -p $(OBJS_DIR)unset
	@echo "$(MENT)[ Created obj directory ... ]$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(HEADERS)
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT_LIB) :
	@$(MAKE) -sC $(LIBFT_DIR)
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@echo "$(YELLOW)[ Created libft.a ... ]$(RESET)"

all : $(NAME)

clean :
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(MENT)[Removing object files]"
	@echo "$(MAGENTA)$(OBJS)$(RESET)"

fclean : clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(MENT)[Removing $(NAME)]$(RESET)"
	@echo "$(NAME):$(MAGENTA) deleted$(RESET)"

ment_re :
	@echo "$(RE_MENT)[make re]$(RESET)"

re : ment_re fclean all
	@echo "$(RE_MENT)[make re done.]$(RESET)"

norm :
	@echo "$(MENT)[Norminette test]$(CYAN)"
	@find ./src -name "*.c" -exec norminette {} \;
	@find ./includes -name "*.h" -exec norminette {} \;
	@echo "$(RESET)"

tester :
	@gcc tester.c libft/libft.a
	@./a.out
