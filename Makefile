# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsilveir <jsilveir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 12:33:45 by jsilveir          #+#    #+#              #
#    Updated: 2025/07/22 13:47:50 by jsilveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=gcc
CFLAGS= -Wall -Wextra -Werror 
OBJ_DIR= obj
SRC_DIR= src

SRC_FILES= utils.c time.c routine.c main.c parse.c \
			philo.c philo_utils.c philo_routine.c \
			philo_init.c philo_destroy.c philo_monitor.c \
			philo_print.c

OBJ= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
SRC= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	
fclean: clean
	@rm -rf $(NAME)
	
re: fclean all

.PHONY: all fclean clean re