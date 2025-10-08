
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

# Variables
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = src/pipex.c
OBJS_ = $(SRCS:.c=.o)

# Regla de compilación
all: $(NAME)	
# Compilación del servidor y cliente
$(SERVER): $(OBJS_SERVER) minitalk.h
	$(CC) $(FLAGS) -o $(SERVER) $(OBJS_SERVER)
$(CLIENT): $(OBJS_CLIENT) minitalk.h
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJS_CLIENT)
# Limpieza de archivos objeto y ejecutables
clean:
	$(RM) $(NAME)
# Limpieza completa
fclean: clean
	$(RM) $(NAME)
re: fclean all
# Prevención de conflictos con archivos y directorios
.PHONY: all clean fclean re
=======
# Ejecutables
NAME = pipex
NAME_BONUS = pipex_bonus

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)
RM = rm -f

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
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Reglas de limpieza
clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
re: fclean all
	
# Objetivos que no son archivos
.PHONY: all clean fclean re bonus

