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
CC=cc
CFLAGS= -Wall -Wextra -Werror -g -Imlx -I/usr/include/X11
OBJ_DIR= obj
SRC_DIR= src
LIBFT= libft/libft.a

SRC_FILES= 

OBJ= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
SRC= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

$(LIBFT):
	@make -C ./libft -s
	
$(MLX):
	@make -C ./mlx -s

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C ./libft -s
	@make clean -C ./mlx -s
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	
re: fclean all

.PHONY: all fclean clean re