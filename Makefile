# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 12:58:33 by tiade-al          #+#    #+#              #
#    Updated: 2025/02/21 10:25:15 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(shell find srcs -type f -name "*.c")#can't be delivered like this


OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

CC = @cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo " [ .. ] | Compiling..."
	@make -s -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: srcs/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo " [ OK ] | Completed!"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "All files created were removed."

re: fclean all

.PHONY: all clean fclean re
