# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 16:16:56 by aggrigor          #+#    #+#              #
#    Updated: 2024/04/07 14:08:09 by aggrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = philo

# Compilator
CC = cc
# Compilator flags
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

# Headers
HEADERS = inc/philo.h

# Source directory
SRCS_DIR = src/
# Objects directory
OBJS_DIR = objs/

# Source file names
SRCS_NAME = main.c\
			init_vars.c\
			simulation.c\
			checks.c\
			utils.c\

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lpthread

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# Remaking
re: clean all

# PHONY files
.PHONY: all clean fclean re