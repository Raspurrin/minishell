# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 20:03:25 by mialbert          #+#    #+#              #
#    Updated: 2022/10/03 21:09:35 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror -pthread -g -O3
NAME	= minishell
DEBUG	= -fsanitize=thread
SRCS	=	./srcs/test.c

OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
PURPLE	:= \033[0;35m
B_BLUE 	:= \033[1;34m
BLUE 	:= \033[0;34m

all: minishell

%.o : %.c
	@echo "$(B_BLUE)Compiling: $(BLUE)$(notdir $<) 🔨$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

banner:
	@echo "\n${PURPLE}======== Minishell ========${NC}"

$(NAME): banner $(OBJS)
	@$(CC) -lreadline $(CFLAGS) $(OBJS) -o $(NAME) $(DEBUG)
clean:
	@rm -f $(OBJS)
	@echo "${B_RED}🧹 Cleaning: ${RED} object files $(NC)"

fclean: clean
	@rm -f philo
	@echo "${B_RED}🧹 Cleaning: ${RED} $(NAME)$(NC)"

re: fclean all

.PHONY: all clean fclean re banner $(NAME)
