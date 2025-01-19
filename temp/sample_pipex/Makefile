NAME = pipex

SRC = sample.c
OBJ = $(SRC:.o=.c)

all : $(NAME)

$(NAME): $(OBJ)
	cc -Wall -Wextra -Werror $(OBJ) -o $(NAME)

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@