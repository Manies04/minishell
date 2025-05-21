# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 12:58:33 by tiade-al          #+#    #+#              #
#    Updated: 2025/05/21 01:41:32 by tiade-al         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Colors for terminal output
RESET = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
CYAN = \033[36m

# Source files (explicitly listed to replace dynamic find)
SRCS = srcs/main.c \
	srcs/signals.c \
	srcs/builtins/env_II.c \
	srcs/builtins/env.c \
	srcs/builtins/exit.c \
	srcs/builtins/export_I.c \
	srcs/builtins/export_II.c \
	srcs/builtins/pwd.c \
	srcs/builtins/unset.c \
	srcs/execution/executer.c \
	srcs/execution/file_management.c \
	srcs/execution/handle_fds.c \
	srcs/execution/roundabout.c \
	srcs/expand/expand.c \
	srcs/expand/expand_II.c \
	srcs/expand/expand_III.c \
	srcs/init/global_init.c \
	srcs/parsing/find_errors.c \
	srcs/parsing/lexer.c \
	srcs/parsing/parser_utils.c \
	srcs/parsing/parser_utils2.c \
	srcs/parsing/parser.c \
	srcs/utils/cleaners.c \
	srcs/utils/helpers.c \

# Object files
OBJ = $(SRCS:srcs/%.c=objs/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# Library paths
LIBFT_PATH = inc/Libft
LIBFT = $(LIBFT_PATH)/libft.a

# Default target
all: $(NAME)

# Link executable
$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)[ LINKING ]$(RESET) Linking $(NAME)..."
	@$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)[ OK ]$(RESET) $(NAME) linked."
	@echo "$(GREEN)[ SUCCESS ]$(RESET) $(NAME) built successfully!"

# Build libft
$(LIBFT):
	@echo "$(YELLOW)[ LIBFT ]$(RESET) Compiling libft..."
	@make -s -C $(LIBFT_PATH)
	@echo "$(GREEN)[ OK ]$(RESET) libft compiled."

# Compile source files
objs/%.o: srcs/%.c
	@mkdir -p $(@D)
	@echo "$(CYAN)[ COMPILING ]$(RESET) $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)[ CLEAN ]$(RESET) Removing object files..."
	@rm -rf objs
	@echo "$(GREEN)[ OK ]$(RESET) Object files removed."

# Clean everything
fclean: clean
	@echo "$(RED)[ FCLEAN ]$(RESET) Removing $(NAME) and cleaning libft..."
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_PATH)
	@echo "$(GREEN)[ OK ]$(RESET) All generated files removed."

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re
