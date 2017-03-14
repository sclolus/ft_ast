# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 03:04:06 by aalves            #+#    #+#              #
#    Updated: 2017/03/14 06:31:17 by sclolus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export NAME = libft.a
export CC = gcc
export FLAGS = -Werror -Wall -Wextra -g -O0
export VERBOSE = 0
SRCS =	ft_memset.c \
		ft_pow.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_max.c \
		ft_distance.c \
		ft_strchr_index.c \
		ft_log2.c \
		ft_is_little_endian.c \
		ft_is_power_of_two.c \
		ft_lsttotab.c \
		get_next_line.c \
		ft_lstlen.c \
		ft_print_page.c \
		ft_random.c \
		ft_sort.c \
		ft_strreplace.c \
		ft_strjoin_f.c \
		get_next_line.c \
		ft_stack.c \
		ft_error.c \

OBJS = $(SRCS:.c=.o)

MODULES =	./list/ \
			./ast \


export RM = rm -f
export ECHO = echo

#	COLORS

export BLACK = \033[0;30m
export RED = \033[0;31m
export GREEN = \033[0;32m
export BROWN = \033[0;33m
export BLUE = \033[0;34m
export PURPLE = \033[0;35m
export CYAN = \033[0;36m
export GRAY = \033[0;37m
export NC = \033[0m

ifneq (,$(findstring s,$(MAKEFLAGS)))
	VERBOSE = 0
endif

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I./includes -o $@ -c $<

else
.c.o:
	@$(CC) $(FLAGS) -I./includes -o $@ -c $<
endif

all: $(NAME)

modules:
	@$(foreach module, $(MODULES), make -C $(module);)

$(NAME): $(OBJS) modules
	@ar rc $@ $(OBJS)
	@$(ECHO) "$(CYAN)Main archive done $(NC)"
	@ranlib $@

test: all
	gcc -I./includes -o test test.c libft.a
clean:
	@$(ECHO) "$(CYAN)Cleaning objects $(NC)"
	@$(foreach mod, $(MODULES), make -C $(mod) clean;)
	@$(RM) $(OBJS)
	@$(ECHO) "$(CYAN)Main archive cleaned $(NC)"
	@$(ECHO) "$(CYAN)Done $(NC)"

fclean: clean
	@$(RM) $(NAME)
	@$(ECHO) "$(CYAN)Cleaned archive $(NC)"

re: fclean all
