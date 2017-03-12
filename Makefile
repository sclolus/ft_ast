NAME= ft_ast
CC= gcc
FLAGS= -Wall -Werror -Wextra
SRC=		ast.c \
			main.c \
	ft_grammar.c
OBJ= $(SRC:.c=.o)
HDR_PATH= ./libft/includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $^ -L./libft -lft  $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $< -I$(HDR_PATH) $(FLAGS) -c

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
	make -C libft/ re
