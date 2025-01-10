# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 14:08:28 by cwon              #+#    #+#              #
#    Updated: 2025/01/09 17:22:26 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

src = \
	pipex.c \
	init.c \
	tokenizer.c \
	tokenizer_util.c \
	flush.c \
	error.c \
	protect_file.c \
	protect_process.c \
	protect_string.c
obj = $(src:.c=.o)

lib_dir = libft
lib_name = libft.a
lib_path = $(lib_dir)/$(lib_name)

NAME = pipex
header = pipex.h

all: $(lib_path) $(NAME)

$(lib_path):
	make -C $(lib_dir)

%.o: %.c $(header)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(src) $(obj) $(header) $(lib_path)
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(lib_path)

clean:
	make clean -C $(lib_dir)
	rm -f $(obj) $(bonus_obj)

fclean: clean
	make fclean -C $(lib_dir)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft bonus