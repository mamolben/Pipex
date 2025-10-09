
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

# Ejecutables
NAME = pipex
NAME_BONUS = pipex_bonus

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)
RM = rm -fCC = gcc

# Directorios
SRCDIR = src
OBJDIR = $(SRCDIR)/.o
INCDIR = include

# Fuentesc y objetos
SRC = $(wildcard $(SRCDIR)/*.c)
SRC_BONUS = $(wildcard $(SRCDIR)/*_bonus.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJ_BONUS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_BONUS))

# Regla de compilación
all: $(NAME)

# Compilación de ejecutables y objetos
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
bonus: $(NAME_BONUS)
$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
# Creación del directorio objeto
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpieza de archivos objeto y ejecutables
clean:
	$(RM) $(NAME)
# Limpieza completa
fclean: clean
	$(RM) $(NAME)
re: fclean all
# Prevención de conflictos con archivos y directorios
.PHONY: all clean fclean re bonus