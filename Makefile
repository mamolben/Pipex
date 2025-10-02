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
