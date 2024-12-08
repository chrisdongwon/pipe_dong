# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 16:52:39 by cwon              #+#    #+#              #
#    Updated: 2024/12/06 14:19:45 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

printf_dir = ft_printf

src = \
	$(wildcard *.c) \
	$(wildcard $(printf_dir)/*.c)
obj = $(src:.c=.o)

NAME = libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(obj)
	ar -rcs $(NAME) $(obj)

clean:
	rm -f $(obj)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re