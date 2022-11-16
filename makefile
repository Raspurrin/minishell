# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 18:45:17 by pmoghadd          #+#    #+#              #
#    Updated: 2022/11/16 15:37:12 by pmoghadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJ_DIR =	object_files
CFLAGS	=	-Wall -Wextra -Werror -g
NAME	=	minishell
READLINE = 	-I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
DEBUG	=	-fsanitize=address
LIBFT	=	./libs/libft/
SRCS	=	./srcs/parsing/main2.c \
			./srcs/parsing/initialize.c \
			./srcs/parsing/lexical_scan.c \
			./srcs/parsing/expand.c \
			./srcs/parsing/shell_split.c \
			./srcs/parsing/utils.c \
			./srcs/parsing/check_input.c \
			./srcs/execution/execution.c \
			./srcs/execution/inout_files.c \
			./srcs/builtins/cd.c \
			./srcs/builtins/echo.c \
			./srcs/builtins/env.c \
			./srcs/builtins/exit.c \
			./srcs/builtins/export.c \
			./srcs/builtins/pwd.c \
			./srcs/builtins/unset.c \
			./srcs/main.c \
			./srcs/init.c \
			./srcs/utils.c \
			./srcs/error.c \
			./srcs/free.c

OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
PURPLE	:= \033[0;35m
B_BLUE 	:= \033[1;34m
BLUE 	:= \033[0;34m
FLAGS_OS := -lreadline

SUBM_STATE := $(shell find libs/libft -type f)

ifeq ($(DEBUG),1)	
FSAN 	=	-fsanitize=address
else 
FSAN 	=
endif

ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	= 
endif

all: $(SUBM_FLAG) libft minishell

submodule:
	@git submodule init 
	@git submodule update

%.o : %.c
	@echo "$(B_BLUE)Compiling: $(BLUE)$(notdir $<) 🔨$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

banner:
	@echo "\n${PURPLE}======== Minishell ========$(NC)"

libft: 
	@echo "\n${BLUE}======== Libft ========${NC}"
	@$(MAKE) -C $(LIBFT)

$(NAME): banner $(OBJS)
	@$(CC) $(FLAGS_OS) $(CFLAGS) $(ADDUSER) $(OBJS) $(LIBFT)libft.a $(READLINE) $(FSAN) -o $(NAME)
# $(CDIR) $(TESTER)
# @mkdir object_files
# @mv $(OBJS) object_files

e: all
	./$(NAME)

test: 
	gcc -Wall -Werror -Wextra -g srcs/lltest.c libs/libft/libft.a -fsanitize=address

clean:
	@rm -f $(OBJS)
	@echo "${B_RED}🧹 Cleaning: ${RED} object files $(NC)"

fclean: clean
	@rm -f philo
	@echo "${B_RED}🧹 Cleaning: ${RED} $(NAME)$(NC)"

re: fclean all

.PHONY: all clean fclean re banner $(NAME) libft e submodule
