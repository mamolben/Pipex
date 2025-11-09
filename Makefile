
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

# Nombre del ejecutable
NAME = pipex
NAME_BONUS = pipex_bonus

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -g
RM = rm -f

# Directorios
SRC_DIR = src
SRC_BONUS_DIR = src_bonus
OBJ_DIR = $(SRC_DIR)/.o
OBJ_BONUS_DIR = $(SRC_BONUS_DIR)/.o
INC_DIR = include

# Fuentes y objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
BONUS_OBJS = $(patsubst $(SRC_BONUS_DIR)/%.c,$(OBJ_BONUS_DIR)/%.o,$(SRC_BONUS))


# Reglas de compilación
all: $(NAME)

# pipex
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^

# con _bonus
$(NAME_BONUS): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ $^

# archivos .c a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creación del directorio de objetos
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

# Limpieza 
clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)

# Recompilación
re: fclean all

# Regla para la compilación bonus
bonus: $(NAME_BONUS)

# Prevención de conflictos con archivos y directorios
.PHONY: all clean fclean re bonus
