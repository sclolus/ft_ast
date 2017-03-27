# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 05:34:22 by aalves            #+#    #+#              #
#    Updated: 2017/03/28 01:42:47 by aalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		ft_strndup.c

OBJS = $(SRCS:.c=.o)

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
else
.c.o:
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
endif

all: $(OBJS)
	@$(ECHO) "$(CYAN)Main module done $(NC)"
	@ar r ../$(NAME) $^

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(BLUE)Main module cleaned $(NC)"

re: clean all
