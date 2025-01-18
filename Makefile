# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 14:08:28 by cwon              #+#    #+#              #
#    Updated: 2025/01/18 09:07:54 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
MANDATORY_EXEC = pipex_mandatory
BONUS_EXEC = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

TOKENIZER_HEADER = tokenizer.h
TOKENIZER_SRC = \
	list_util.c \
	tokenizer_util.c \
	tokenizer.c

HEADER = pipex.h
SRC = \
	flush_pipex.c \
	path.c \
	pipex_util.c \
	pipex.c
OBJ = $(SRC:.c=.o) $(TOKENIZER_SRC:.c=.o)

BONUS_SRC = \
	pipex_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o) $(TOKENIZER_SRC:.c=.o)

all: $(MANDATORY_EXEC)
	@ln -sf $(MANDATORY_EXEC) $(NAME)

$(MANDATORY_EXEC): $(OBJ) $(HEADER) $(TOKENIZER_HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(MANDATORY_EXEC)

$(NAME): $(MANDATORY_EXEC)

bonus: $(BONUS_EXEC)
	@ln -sf $(BONUS_EXEC) $(NAME)

$(BONUS_EXEC): $(BONUS_OBJ) $(HEADER) $(TOKENIZER_HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(MANDATORY_EXEC) $(BONUS_EXEC) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus