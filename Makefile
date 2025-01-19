# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 14:08:28 by cwon              #+#    #+#              #
#    Updated: 2025/01/19 17:32:59 by cwon             ###   ########.fr        #
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
	pipex_flush.c \
	pipex_path.c \
	pipex_util.c \
	pipex.c
OBJ = $(SRC:.c=.o) $(TOKENIZER_SRC:.c=.o)

BONUS_SRC = \
	pipex_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o) $(TOKENIZER_SRC:.c=.o)

all: $(MANDATORY_EXEC)
	@ln -sf $(MANDATORY_EXEC) $(NAME)

$(MANDATORY_EXEC): $(LIBFT) $(OBJ) $(HEADER) $(TOKENIZER_HEADER) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(MANDATORY_EXEC)

$(NAME): $(MANDATORY_EXEC)

# bonus: $(BONUS_EXEC)
# 	@ln -sf $(BONUS_EXEC) $(NAME)

$(BONUS_EXEC): $(LIBFT) $(BONUS_OBJ) $(HEADER) $(TOKENIZER_HEADER)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_EXEC)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(MANDATORY_EXEC) $(BONUS_EXEC) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus