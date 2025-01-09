# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 14:08:28 by cwon              #+#    #+#              #
#    Updated: 2025/01/09 12:48:56 by cwon             ###   ########.fr        #
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

bonus_src = \
	pipex_bonus.c \
	init_bonus.c \
	tokenizer.c \
	tokenizer_util.c \
	flush_bonus.c \
	error_bonus.c \
	protect_file_bonus.c \
	protect_process_bonus.c \
	protect_string_bonus.c
bonus_obj = $(bonus_src:.c=.o)

lib_dir = libft
lib_name = libft.a
lib_path = $(lib_dir)/$(lib_name)

NAME = pipex
header = pipex.h
bonus_header = pipex_bonus.h

all: $(lib_path) $(NAME)

bonus: $(bonus_src) $(bonus_obj) $(bonus_header) $(lib_path)
	$(CC) $(CFLAGS) $(bonus_obj) -o $(NAME) $(lib_path)

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