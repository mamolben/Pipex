
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marimoli <marimoli@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/02 16:05:37 by marimoli          #+#    #+#              #
#    Updated: 2025/10/02 16:05:51 by marimoli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ======================= Executables, Compiler, Flags ======================= #
NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
RM = rm -f

# ======================= Directory ======================= #
SRC_DIR = src
SRC_BONUS_DIR = src_bonus
SRC_COMMON_DIR = src_common

OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

# ======================= File Source and Object ======================= #

# Comunes #
COMMON_SRCS = $(wildcard $(SRC_COMMON_DIR)/*.c)

# Obligatorio #
MANDATORY_SRCS = $(wildcard $(SRC_DIR)/*.c)

# Bonus #
BONUS_SRCS = $(wildcard $(SRC_BONUS_DIR)/*.c)

SRC = $(MANDATORY_SRCS) $(COMMON_SRCS)
SRC_BONUS = $(BONUS_SRCS) $(COMMON_SRCS)

# Objetos #
OBJS = $(SRC:%=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(SRC_BONUS:%=$(OBJ_BONUS_DIR)/%.o)

# ======================= Rules # =======================

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# regla general para compilar .c a .o
$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re