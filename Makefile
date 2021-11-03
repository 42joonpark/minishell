CC			:= 	gcc
CFLAGS		:= 	-g -Wall -Wextra -Werror

RDLINE_DIR	:= /Users/donpark/brew/opt/readline/lib/
RDLINE_INC	:= /Users/donpark/brew/opt/readline/include/

LIBFT_DIR = ./libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
LIBFT_INC = $(LIBFT_DIR)

INC_DIR = ./includes/
INCLUDES = minishell.h
INCS = $(addprefix $(INC_DIR), $(INCLUDES))

SRCS_DIR	:=	./src/
SOURCES		:=	main.c \
				test.c \
				loop.c \
				parse_line.c \
				modify_arg_type.c \
				check_builtin.c \
				check_dollar.c \
				execute.c \
				clear.c \
				error.c \
				pwd/pwd.c \
				echo/echo.c \
				cd/cd.c \
				env/env_list.c \
				env/env.c \
				export/export_list.c \
				export/export.c \
				export/export_utils.c \
				export/export_add_env.c \
				export/export_add_exp.c \
				unset/unset.c \
				utils/pp_strdup.c
				utils/pp_split.c \
				utils/pp_strlen.c \
				utils/pp_strcmp.c \
				utils/pp_strcmp_limit.c \
				utils/free.c \
				utils/pp_memset.c \
				utils/pp_lst.c \
				utils/pp_strlcpy.c \
				utils/pp_strjoin.c \
				utils/pp_substr.c \
				utils/pp_which.c \
				utils/get_next_line.c \
				utils/get_next_line_utils.c
SRCS		:=	$(addprefix $(SRCS_DIR), $(SOURCES))


OBJS_DIR	:=	./obj/
OBJECTS		:=	$(SOURCES:.c=.o)
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJECTS))

LIBRARY		:= -L$(RDLINE_DIR) -lreadline -L$(LIBFT_DIR) -lft
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

.PHONY		:=	all ment_re $(NAME) bonus clean fclean re

$(NAME) : $(OBJS_DIR) $(OBJS) $(LIBFT_LIB)
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
	@echo "\n$(YELLOW)[ Created libft.a ... ]$(RESET)"

all : $(NAME)

ment_re :
	@echo "$(RE_MENT)[make re]$(RESET)"

bonus : $(OBJS) $(BNS_OBJ)
	@$(CC) -o $(NAME) $(OBJS)
	@echo "\n$(GREEN)bonus object files were created$(RESET)"
	@echo "$(GREEN)$(NAME) was created$(RESET)"

clean :
	@rm -rf $(OBJS_DIR)
	@echo "$(MENT)[Removing object files]"
	@echo "$(MAGENTA)$(OBJS)$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(MENT)[Removing $(NAME)]$(RESET)"
	@echo "$(NAME):$(MAGENTA) deleted$(RESET)"

re : ment_re fclean all
	@echo "$(RE_MENT)[make re done.]$(RESET)"

norm_test :
	@echo "$(MENT)[Norminette test]$(CYAN)"
	@find ./src -name "*.c" -exec norminette {} \;
	@find ./includes -name "*.h" -exec norminette {} \;

