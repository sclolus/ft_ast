NAME= ft_ast
CC= gcc
FLAGS= -Wall  -Wextra -g3 -fsanitize=address
SRC= srcs/main.c \
	srcs/ast/ast.c \
	srcs/ast/ft_put_parser.c \
	srcs/ast/ft_assign_parsers.c \
	srcs/ast/ft_dup_parser/ft_dup_parser.c \
	srcs/ast/ft_eval_parser.c \
	srcs/ast/ft_eval_parser_chars.c \
	srcs/ast/ft_eval_parser_logical.c \
	srcs/ast/ft_eval_parser_misc.c \
	srcs/ast/ft_eval_parser_multiply.c \
	srcs/ast/ft_eval_parser_plus.c \
	srcs/ast/ft_eval_parser_strings.c \
	srcs/ast/ft_eval_parser_str_any_of.c \
	srcs/ast/ft_free_parser/ft_free_parser.c \
	srcs/ast/ft_free_parser/ft_free_parser_chars.c \
	srcs/ast/ft_free_parser/ft_free_parser_logicals.c \
	srcs/ast/ft_free_parser/ft_free_parser_misc.c \
	srcs/ast/ft_free_parser/ft_free_parser_strings.c \
	srcs/ast/ft_get_grammar.c \
	srcs/ast/ft_get_grammar_linker.c \
	srcs/ast/ft_get_grammar_syntax.c \
	srcs/ast/ft_get_parser.c \
	srcs/ast/ft_get_parser_chars.c \
	srcs/ast/ft_get_parser_grammar.c \
	srcs/ast/ft_get_parser_logicals.c \
	srcs/ast/ft_get_parser_misc.c \
	srcs/ast/ft_get_parser_strings.c \
	srcs/ast/ft_get_parser_terminals.c \
	srcs/ast/ft_optimizer.c \
	srcs/ast/ft_sanitizer/ft_sanitizer.c \
	srcs/ast/ft_sanitizer/ft_sanitizer_chars.c \
	srcs/ast/ft_sanitizer/ft_sanitizer_logicals.c \
	srcs/ast/ft_sanitizer/ft_sanitizer_misc.c \
	srcs/ast/ft_sanitizer/ft_sanitizer_strings.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_chars.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_logicals.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_multiply.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_plus.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_misc.c \
	srcs/ast/ft_eval_tokens/ft_eval_tokens_strings.c
OBJ= $(SRC:.c=.o)
HDR_PATHS= ./includes ./libft/includes
HDR_FLAGS= $(addprefix -I, $(HDR_PATHS))
HDR_PATH= ./includes ./libft/includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $^ -L./libft -lft  -lreadline $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $< $(HDR_FLAGS) $(FLAGS) -o $@ -c

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
