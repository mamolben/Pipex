
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

# Para bonus #
SRC = $(MANDATORY_SRCS) $(COMMON_SRCS)
SRC_BONUS = $(BONUS_SRCS) $(COMMON_SRCS)

# Objetos #
OBJS = $(SRC:%=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(SRC_BONUS:%=$(OBJ_BONUS_DIR)/%.o)

# ======================= Reglas # =======================

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
# **************************************************************************** #

# Executable
#NAME = pipex
#NAME_BONUS = pipex_bonus

# Compiler and flags
#CC = cc
#CFLAGS = -Wall -Wextra -Werror -I./include -g
#RM = rm -f

# Directories
#SRC_DIR = src
#SRC_BONUS_DIR = src_bonus
#OBJ_DIR = obj
#OBJ_BONUS_DIR = obj_bonus
#INC_DIR = include

# Sources y objetos
#SRC = $(wildcard $(SRC_DIR)/*.c)
#SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c) $(wildcard $(SRC_DIR)/*.c)
#Se añade $(wildcard $(SRC_DIR)/*.c) para compilar también las fuentes comunes
#OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#BONUS_OBJS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Reglas principales
#all: $(NAME)

#bonus: $(NAME_BONUS)

# pipex
#$(NAME): $(OBJS)
#	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^

# pipex_bonus
#$(NAME_BONUS): $(BONUS_OBJS)
#	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^

# Compilación .c a .o
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@

#$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@

# Creación del directorio de objetos
#$(OBJ_DIR):
#	mkdir -p $(OBJ_DIR)

#$(OBJ_BONUS_DIR):
#	mkdir -p $(OBJ_BONUS_DIR)

# Limpieza
#clean:
#	@$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)

#fclean: clean
#	@$(RM) $(NAME) $(NAME_BONUS)

#re: fclean all

#.PHONY: all clean fclean re bonus
