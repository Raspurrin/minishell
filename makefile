# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 18:45:17 by pmoghadd          #+#    #+#              #
#    Updated: 2022/10/13 15:16:28 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CFLAGS	=	-Wall -Wextra -Werror -pthread -g
NAME	=	minishell
DEBUG	=	-fsanitize=address
LIBFT	=	./libs/libft/
SRCS	=	./srcs/main.c \
			./srcs/execution/execution.c \
			./srcs/execution/inout_files.c \
			./srcs/init.c \
			./srcs/utils.c \
			./srcs/error.c \
			./srcs/builtins/cd.c \
			./srcs/builtins/echo.c \
			./srcs/builtins/env.c \
			./srcs/builtins/exit.c \
			./srcs/builtins/export.c \
			./srcs/builtins/pwd.c \
			./srcs/builtins/unset.c

OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
PURPLE	:= \033[0;35m
B_BLUE 	:= \033[1;34m
BLUE 	:= \033[0;34m
FLAGS_OS = -lreadline

SUBM_STATE := $(shell find libs/libft -type f)

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
	@$(CC) $(FLAGS_OS) $(CFLAGS) $(OBJS) $(LIBFT)libft.a -o $(NAME) $(DEBUG)

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
